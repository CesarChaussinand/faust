/************************************************************************
 ************************************************************************
 FAUST compiler
    Copyright (C) 2003-2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/
#include <sstream>

#include "Text.hh"
#include "global.hh"
#include "loop.hh"

using namespace std;

/**
 * Print a list of lines
 * @param n number of tabs of indentation
 * @param lines list of lines to be printed
 * @param fout output stream
 */
static void XXXprintlines(int n, list<OldStatement>& lines, ostream& fout)
{
    list<OldStatement>::iterator s;
    string                       ccond = "";
    for (s = lines.begin(); s != lines.end(); s++) {
        if (s->hasCondition(ccond)) {
            tab(n, fout);
            fout << s->thenCode();
        } else if (ccond == "") {
            // debut d'une condition
            ccond = s->condition();
            tab(n, fout);
            fout << "if (" << ccond << ") {";
            n++;
            tab(n, fout);
            fout << s->thenCode();
        } else {
            // fin précédente condition
            n--;
            tab(n, fout);
            fout << "}";
            // nouvelle condition courante
            ccond = s->condition();
            if (ccond != "") {
                tab(n, fout);
                fout << "if (" << ccond << ") {";
                n++;
            }
            tab(n, fout);
            fout << s->thenCode();
        }
    }
    if (ccond != "") {
        n--;
        tab(n, fout);
        fout << "}";
    }
}

/**
 * @brief
 *
 * @param n
 * @param lines
 * @param fout
 */
static void printThenLines(int n, list<OldStatement>& lines, ostream& fout)
{
    for (auto s : lines) {
        tab(n, fout);
        fout << s.thenCode();
    }
}

/**
 * @brief
 *
 * @param n
 * @param lines
 * @param fout
 */
static void printElseLines(int n, list<OldStatement>& lines, ostream& fout)
{
    for (auto s : lines) {
        if (s.elseCode().size() > 0) {
            tab(n, fout);
            fout << s.elseCode();
        }
    }
}

/**
 * @brief Print a group of statements with a common condition
 *
 * @param n indentation
 * @param ccond possibly empty common condition
 * @param group list of statements
 * @param fout output stream
 */
static void printSameCondGroup(int n, const string& ccond, list<OldStatement>& group, ostream& fout)
{
    if (ccond.size() == 0) {
        printThenLines(n, group, fout);
    } else {
        std::stringstream thencode, elsecode;
        printThenLines(n + 1, group, thencode);
        printElseLines(n + 1, group, elsecode);
        std::string thenstring = thencode.str();
        std::string elsestring = elsecode.str();

        std::cerr << "ELSE STRING IS:\n" << elsestring << "\nEND" << std::endl;
        if (elsestring.size() == 0) {
            tab(n, fout);
            fout << "if (" << ccond << ") { /" << __FILE__ << ":" << __LINE__;
            fout << thenstring << std::endl;
            tab(n, fout);
            fout << "}";
        } else {
            tab(n, fout);
            fout << "if (" << ccond << ") { /" << __FILE__ << ":" << __LINE__;
            fout << thenstring << std::endl;
            tab(n, fout);
            fout << "} else { // TRACE2 ";
            fout << elsestring << std::endl;
            tab(n, fout);
            fout << "}";
        }
    }
}

/**
 * @brief print a group of lines with arbitrary conditions
 *
 * @param n
 * @param lines
 * @param fout
 */
static void printlines(int n, list<OldStatement>& lines, ostream& fout)
{
    list<OldStatement> group;  // group of  successive lines of same condition
    string             ccond;  // current condition

    for (auto s : lines) {
        if (ccond == s.condition()) {
            // same group
            group.push_back(s);
        } else {
            // we end and print the current group
            printSameCondGroup(n, ccond, group, fout);
            // we start a new group
            group.clear();
            ccond = s.condition();
            group.push_back(s);
        }
    }
    printSameCondGroup(n, ccond, group, fout);
}

/**
 * Create a recursive loop
 * @param recsymbol the recursive symbol defined in this loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Tree recsymbol, Loop* encl, const string& size, const string& cond)
    : fIsRecursive(true),
      fRecSymbolSet(singleton(recsymbol)),
      fEnclosingLoop(encl),
      fSize(size),
      fCond(cond),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * Create a non recursive loop
 * @param encl the enclosing loop
 * @param size the number of iterations of the loop
 */
Loop::Loop(Loop* encl, const string& size, const string& cond)
    : fIsRecursive(false),
      fRecSymbolSet(gGlobal->nil),
      fEnclosingLoop(encl),
      fSize(size),
      fCond(cond),
      fOrder(-1),
      fIndex(-1),
      fUseCount(0),
      fPrinted(0)
{
}

/**
 * A loop with recursive dependencies can't be run alone.
 * It must be included into another loop.
 * returns true is this loop has recursive dependencies
 * and must be included in an enclosing loop
 */

bool Loop::hasRecDependencyIn(Tree S)
{
    Loop* l = this;
    while (l && isNil(setIntersection(l->fRecSymbolSet, S))) l = l->fEnclosingLoop;
    return l != 0;
}

/**
 * Test if a loop is empty that is if it contains no lines of code.
 * @return true if the loop is empty
 */
bool Loop::isEmpty()
{
    return fPreCode.empty() && fExecCode.empty() && fPostCode.empty() && (fExtraLoops.begin() == fExtraLoops.end());
}

/**
 * Add a line of pre code (begin of the loop)
 */
void Loop::addPreCode(const OldStatement& stmt)
{
    cerr << this << "->addExecCode " << stmt << endl;
    fPreCode.push_back(stmt);
}

/**
 * Add a line of exec code
 */
void Loop::addExecCode(const OldStatement& stmt)
{
    cerr << "LOOP : " << this << "->addExecCode " << stmt << endl;
    fExecCode.push_back(stmt);
}

/**
 * Add a line of post exec code (end of the loop)
 */
void Loop::addPostCode(const OldStatement& stmt)
{
    cerr << this << "->addPostCode " << stmt << endl;
    fPostCode.push_front(stmt);
}

/**
 * Absorb a loop by copying its recursive dependencies, its loop dependencies
 * and its lines of exec and post exec code.
 * @param l the Loop to be absorbed
 */
void Loop::absorb(Loop* l)
{
    // the loops must have the same number of iterations
    // cerr << "Loop absorbtion : " << this << " absorb " << l << endl;
    faustassert(fSize == l->fSize);
    fRecSymbolSet = setUnion(fRecSymbolSet, l->fRecSymbolSet);

    // update loop dependencies by adding those from the absorbed loop
    fBackwardLoopDependencies.insert(l->fBackwardLoopDependencies.begin(), l->fBackwardLoopDependencies.end());

    // add the line of code of the absorbed loop
    fPreCode.insert(fPreCode.end(), l->fPreCode.begin(), l->fPreCode.end());
    fExecCode.insert(fExecCode.end(), l->fExecCode.begin(), l->fExecCode.end());
    fPostCode.insert(fPostCode.begin(), l->fPostCode.begin(), l->fPostCode.end());
}

const string Loop::getCommonCondition()
{
    if (fCond.size() > 0) {
        return fCond;
    } else {
        bool   init = true;
        string CC;
        for (auto s : fExecCode) {
            if (init) {
                CC   = s.condition();
                init = false;
            } else {
                if (CC != s.condition()) return "";
            }
        }
        return CC;
    }
}

/**
 * @brief convert an old statement into a new statement
 *
 * @param s
 * @return Statement
 */
static Statement old2newStatement(const OldStatement& s)
{
    if (s.hasCondition()) {
        if (s.elseCode() != "") {
            return cond(s.condition(), instr(s.thenCode()), instr(s.elseCode()));
        } else {
            return cond(s.condition(), instr(s.thenCode()));
        }
    } else {
        return instr(s.thenCode());
    }
}

/**
 * @brief convert a loop into a block of (new) statements
 *
 * @param b
 */

void Loop::loop2block(Block& b)
{
    for (Loop* l : fExtraLoops) {
        l->loop2block(b);
    }

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        for (auto s : fPreCode) b.push_back(old2newStatement(s));

        if (fExecCode.size() > 0) {
            Block l;
            for (auto s : fExecCode) l.push_back(old2newStatement(s));
            b.push_back(loop(subst("int i=0; i<$0; i++", fSize), l));
        }

        for (auto s : fPostCode) b.push_back(old2newStatement(s));
    } else {
        b.push_back(instr("// empty loop "));
    }
}

/**
 * Print a loop (unless it is empty)
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::println(int n, ostream& fout)
{
    for (Loop* l : fExtraLoops) {
        l->println(n, fout);
    }

    tab(n, fout);
    fout << "// Extra loops  : ";
    for (Loop* l : fExtraLoops) fout << l << " ";

    tab(n, fout);
    fout << "// Backward loops: ";
    bool emptyflag = true;
    for (Loop* l : fBackwardLoopDependencies) {
        emptyflag = false;
        fout << l << " ";
    }  ///< Loops that must be computed before this one
    if (emptyflag) fout << "WARNING EMPTY";

    tab(n, fout);
    fout << "// Forward loops : ";
    for (Loop* l : fForwardLoopDependencies) fout << l << " ";

    tab(n, fout);
    fout << "// " << ((fIsRecursive) ? "Recursive" : "Vectorizable") << " loop " << this;

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "// pre processing";
            printlines(n, fPreCode, fout);
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        string CC = getCommonCondition();
        if (CC.size() > 0) {
            // Analyse the then and else code to
            // choose betwen
            //      if (c) {thencode}
            // and
            //      if (c) {thencode} else {elsecode}
            //
            std::stringstream thencode, elsecode;
            printThenLines(n + 2, fExecCode, thencode);
            printElseLines(n + 2, fExecCode, elsecode);
            std::string thenstring = thencode.str();
            std::string elsestring = elsecode.str();

            fout << "if (" << CC << ") {";
            tab(n + 1, fout);
            fout << "for (int i=0; i<" << fSize << "; i++) { // bidule 1";
            fout << thenstring;
            tab(n + 1, fout);
            fout << "}";
            tab(n, fout);
            if (elsestring.size() > 0) {
                fout << "} else {";
                tab(n + 1, fout);
                fout << "for (int i=0; i<" << fSize << "; i++) { // bidule 2";
                fout << elsestring;
                tab(n + 1, fout);
                fout << "}";
                tab(n, fout);
            }
            fout << "}";
        } else {
            fout << "for (int i=0; i<" << fSize << "; i++) { // no cond";
            printlines(n + 1, fExecCode, fout);
            tab(n, fout);
            fout << "}";
        }

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "// post processing";
            printlines(n, fPostCode, fout);
        }
        tab(n, fout);
    } else {
        fout << "// empty loop " << this;
    }
}

/**
 * Print a parallel loop (unless it is empty). Should be called only for loop
 * without pre and post processing
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printParLoopln(int n, ostream& fout)
{
    for (list<Loop*>::const_iterator s = fExtraLoops.begin(); s != fExtraLoops.end(); s++) {
        tab(n, fout);
        fout << "#pragma omp single";
        tab(n, fout);
        fout << "{";
        (*s)->println(n + 1, fout);
        tab(n, fout);
        fout << "}";
    }

    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        tab(n, fout);
        fout << "// LOOP " << this;
        if (fPreCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
            tab(n, fout);
            fout << "}";
        }

        tab(n, fout);
        fout << "// exec code";
        tab(n, fout);
        fout << "#pragma omp for";
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        printlines(n + 1, fExecCode, fout);
        tab(n, fout);
        fout << "}";

        if (fPostCode.size() > 0) {
            tab(n, fout);
            fout << "#pragma omp single";
            tab(n, fout);
            fout << "{";
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
            tab(n, fout);
            fout << "}";
        }
        tab(n, fout);
    }
}

/**
 * Print a single loop (unless it is empty)
 * @param n number of tabs of indentation
 * @param fout output stream
 */
void Loop::printoneln(int n, ostream& fout)
{
    if (fPreCode.size() + fExecCode.size() + fPostCode.size() > 0) {
        tab(n, fout);
        fout << "for (int i=0; i<" << fSize << "; i++) {";
        if (fPreCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// pre processing";
            printlines(n + 1, fPreCode, fout);
        }
        printlines(n + 1, fExecCode, fout);
        if (fPostCode.size() > 0) {
            tab(n + 1, fout);
            fout << "// post processing";
            printlines(n + 1, fPostCode, fout);
        }
        tab(n, fout);
        fout << "}";
    }
}

//-------------------------------------------------------
void Loop::concat(Loop* l)
{
    faustassert(l->fUseCount == 1);
    faustassert(fBackwardLoopDependencies.size() == 1);
    faustassert((*fBackwardLoopDependencies.begin()) == l);

    fExtraLoops.push_front(l);
    fBackwardLoopDependencies = l->fBackwardLoopDependencies;
}
