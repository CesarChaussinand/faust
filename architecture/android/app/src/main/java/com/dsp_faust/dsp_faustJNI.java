/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dsp_faust;

public class dsp_faustJNI {

  static {
    try {
        java.lang.System.loadLibrary("dsp_faust");
    } catch (UnsatisfiedLinkError e) {
        java.lang.System.err.println("native code library failed to load.\n" + e);
        java.lang.System.exit(1);
    }
  }

  public final static native boolean init(int jarg1, int jarg2);
  public final static native boolean start();
  public final static native void stop();
  public final static native void destroy();
  public final static native boolean isRunning();
  public final static native int keyOn(int jarg1, int jarg2);
  public final static native int keyOff(int jarg1);
  public final static native String getJSON();
  public final static native int getParamsCount();
  public final static native void setParamValue(String jarg1, float jarg2);
  public final static native float getParamValue(String jarg1);
  public final static native void setVoiceParamValue(String jarg1, int jarg2, float jarg3);
  public final static native float getVoiceParamValue(String jarg1, int jarg2);
  public final static native String getParamAddress(int jarg1);
  public final static native void propagateAcc(int jarg1, float jarg2);
  public final static native void setAccConverter(int jarg1, int jarg2, int jarg3, float jarg4, float jarg5, float jarg6);
  public final static native void propagateGyr(int jarg1, float jarg2);
  public final static native void setGyrConverter(int jarg1, int jarg2, int jarg3, float jarg4, float jarg5, float jarg6);
  public final static native void propagateMidi(int jarg1, double jarg2, int jarg3, int jarg4, int jarg5, int jarg6);
  public final static native float getCPULoad();
  public final static native int getScreenColor();
}