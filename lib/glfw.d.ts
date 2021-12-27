export const enum BOOL {
  TRUE = 1,
  FALSE = 0,
}
export const enum ACTION {
  RELEASE = 0,
  PRESS = 1,
  REPEAT = 2,
}
export const enum HAT_STATE {
  CENTERED = 0,
  DOWN = 4,
  LEFT = 8,
  LEFT_DOWN = 0xc,
  LEFT_UP = 0x9,
  RIGHT = 2,
  RIGHT_DOWN = 0x6,
  RIGHT_UP = 0x3,
  UP = 1,
}
export const enum MODIFIER_KEY_FLAGS {
  ALT = 0x0004,
  CAPS_LOCK = 0x0010,
  CONTROL = 0x0002,
  NUM_LOCK = 0x0020,
  SHIFT = 0x0001,
  SUPER = 0x0008,
}
export const enum DECIDE_EVENT {
  CONNECTED = 0x00040001,
  DISCONNECTED = 0x00040002,
}

declare interface Long {
  low: number;
  high: number;
}

declare interface Point {
  x: number;
  y: number;
}
declare interface Size {
  width: number;
  height: number;
}
declare interface Scale {
  xscale: number;
  yscale: number;
}
declare interface Workarea {
  x: number;
  y: number;
  width: number;
  height: number;
}
declare interface Rect {
  left: number;
  top: number;
  right: number;
  bottom: number;
}

declare interface GLFWError {
  state: number;
  descriptor?: string;
}

declare interface GamepadState {
  buttons: number[];
  axes: number[];
}
declare interface GammaRamp {
  red: number[];
  green: number[];
  blue: number[];
}
declare interface VideoMode {
  redBits: number;
  greenBits: number;
  blueBits: number;
  refreshRate: number;
  width: number;
  height: number;
}

declare type GLFWwindow = Long;
declare type GLFWmonitor = Long;
declare type GLFWimage = Long;

declare const CXX_glfwInit: () => number;
declare const CXX_glfwTerminate: () => void;
declare const CXX_glfwCreateWindow: (
  width: number,
  height: number,
  title: string,
  monitor?: GLFWmonitor,
  share?: GLFWwindow
) => GLFWwindow;
declare const CXX_glfwPollEvents: () => void;
declare const CXX_glfwWindowShouldClose: (win: GLFWwindow) => boolean;
declare const CXX_glfwGetKey: (win: GLFWwindow, key: number) => number;
declare const CXX_glfwGetMouseButton: (win: GLFWwindow, key: number) => number;
declare const CXX_glfwGetClipboardString: (win: GLFWwindow) => string;
declare const CXX_glfwGetCurrentContext: () => GLFWwindow;
declare const CXX_glfwGetCursorPos: (win: GLFWwindow) => Point;
declare const CXX_glfwGetError: () => GLFWError;
declare const CXX_glfwGetFramebufferSize: (win: GLFWwindow) => Size;
declare const CXX_glfwGetGamepadName: (jid: number) => string;
declare const CXX_glfwGetGamepadState: (
  jid: number
) => GamepadState & { result: number };
declare const CXX_glfwGetGammaRamp: (monitor: GLFWmonitor) => GammaRamp;
declare const CXX_glfwGetInputMode: (win: GLFWwindow, mode: number) => number;
declare const CXX_glfwGetJoystickAxes: (jid: number) => number[];
declare const CXX_glfwGetJoystickButtons: (jid: number) => number[];
declare const CXX_glfwGetJoystickGUID: (jid: number) => string;
declare const CXX_glfwGetJoystickHats: (jid: number) => number[];
declare const CXX_glfwGetJoystickName: (jid: number) => string;
declare const CXX_glfwGetKeyName: (key: number, scancode: number) => string;
declare const CXX_glfwGetKeyScancode: (key: number) => number;
declare const CXX_glfwGetMonitorContentScale: (monitor: GLFWmonitor) => Scale;
declare const CXX_glfwGetMonitorName: (monitor: GLFWmonitor) => string;
declare const CXX_glfwGetMonitorPhysicalSize: (monitor: GLFWmonitor) => Size;
declare const CXX_glfwGetMonitorPos: (monitor: GLFWmonitor) => Point;
declare const CXX_glfwGetMonitors: () => GLFWmonitor[];
declare const CXX_glfwGetMonitorWorkarea: (monitor: GLFWmonitor) => Workarea;
declare const CXX_glfwGetPrimaryMonitor: () => GLFWmonitor;
declare const CXX_glfwGetProcAddress: (name: string) => Long;
declare const CXX_glfwGetRequiredInstanceExtensions: () => string[];
declare const CXX_glfwGetTime: () => number;
declare const CXX_glfwGetTimerFrequency: () => number;
declare const CXX_glfwGetTimerValue: () => number;
declare const CXX_glfwGetVersion: () => {
  major: number;
  minor: number;
  revision: number;
};
declare const CXX_glfwGetVersionString: () => string;
declare const CXX_glfwGetVideoMode: (monitor: GLFWmonitor) => VideoMode;
declare const CXX_glfwGetVideoModes: (monitor: GLFWmonitor) => VideoMode[];
declare const CXX_glfwGetWindowAttrib: (
  win: GLFWwindow,
  attr: number
) => number;
declare const CXX_glfwGetWindowContentScale: (win: GLFWwindow) => Scale;
declare const CXX_glfwGetWindowFrameSize: (win: GLFWwindow) => Rect;
declare const CXX_glfwGetWindowMonitor: (win: GLFWwindow) => GLFWmonitor;
declare const CXX_glfwGetWindowOpacity: (win: GLFWwindow) => number;
declare const CXX_glfwGetWindowPos: (win: GLFWwindow) => Point;
declare const CXX_glfwGetWindowSize: (win: GLFWwindow) => Size;
declare const CXX_glfwCreateCursor: (
  img: GLFWimage,
  x: number,
  y: number
) => Long;
declare const CXX_glfwCreateStandardCursor: (shape: number) => Long;
declare const CXX_glfwDefaultWindowHints: () => void;
declare const CXX_glfwDestroyCursor: (cursor: Long) => void;
declare const CXX_glfwDestroyWindow: (window: GLFWwindow) => void;
declare const CXX_glfwExtensionSupported: (name: string) => number;
declare const CXX_glfwFocusWindow: (win: GLFWwindow) => void;
declare const CXX_glfwHideWindow: (win: GLFWwindow) => void;
declare const CXX_glfwIconifyWindow: (win: GLFWwindow) => void;
declare const CXX_glfwInitHint: (hint: number, value: number) => void;
declare const CXX_glfwJoystickIsGamepad: (jid: number) => number;
declare const CXX_glfwJoystickPresent: (jid: number) => number;
declare const CXX_glfwMakeContextCurrent: (win: GLFWwindow) => void;
declare const CXX_glfwMaximizeWindow: (win: GLFWwindow) => void;
declare const CXX_glfwPostEmptyEvent: () => void;
declare const CXX_glfwRawMouseMotionSupported: () => number;
declare const CXX_glfwRequestWindowAttention: (win: GLFWwindow) => void;
declare const CXX_glfwRestoreWindow: (win: GLFWwindow) => void;
declare const CXX_glfwSetClipboardString: (
  win: GLFWwindow,
  str: string
) => void;
declare const CXX_glfwSetCursor: (win: GLFWwindow, cursor: Long) => void;
declare const CXX_glfwSetCursorPos: (
  win: GLFWwindow,
  x: number,
  y: number
) => void;
declare const CXX_glfwSetGamma: (win: GLFWwindow, gamma: number) => void;
declare const CXX_glfwSetGammaRamp: (win: GLFWwindow, ramp: GammaRamp) => void;
declare const CXX_glfwSetInputMode: (
  win: GLFWwindow,
  mod: number,
  value: number
) => void;
declare const CXX_glfwSetWindowAspectRatio: (
  win: GLFWwindow,
  numer: number,
  denom: number
) => void;
declare const CXX_glfwSetWindowAttrib: (
  win: GLFWwindow,
  attr: number,
  value: number
) => void;
declare const CXX_glfwSetWindowIcon: (
  win: GLFWwindow,
  images: GLFWimage[]
) => void;
declare const CXX_glfwSetWindowMonitor: (
  win: GLFWwindow,
  monitor: GLFWmonitor | undefined,
  xpos: number,
  ypos: number,
  width: number,
  height: number,
  refreshRate: number
) => void;
declare const CXX_glfwSetWindowOpacity: (
  win: GLFWwindow,
  opacity: number
) => void;
declare const CXX_glfwSetWindowPos: (
  win: GLFWwindow,
  x: number,
  y: number
) => void;
declare const CXX_glfwSetWindowShouldClose: (
  win: GLFWwindow,
  flag: boolean
) => void;
declare const CXX_glfwSetWindowSize: (
  win: GLFWwindow,
  width: number,
  height: number
) => void;
declare const CXX_glfwSetWindowSizeLimits: (
  win: GLFWwindow,
  minWidth: number,
  minHeight: number,
  maxWidth: number,
  maxHeight: number
) => void;
declare const CXX_glfwSetWindowTitle: (win: GLFWwindow, title: string) => void;
declare const CXX_glfwShowWindow: (win: GLFWwindow) => void;
declare const CXX_glfwSwapBuffers: (win: GLFWwindow) => void;
declare const CXX_glfwSwapInterval: (win: GLFWwindow, interval: number) => void;
declare const CXX_glfwUpdateGamepadMappings: (name: string) => number;
declare const CXX_glfwVulkanSupported: () => number;
declare const CXX_glfwWaitEvents: () => void;
declare const CXX_glfwWaitEventsTimeout: (timeout: number) => void;
declare const CXX_glfwWindowHint: (hint: number, value: number) => void;
declare const CXX_glfwWindowHintString: (hint: number, value: string) => void;
declare const CXX_glfwSetKeyCallback: (
  win: GLFWwindow,
  callback?: (
    win: GLFWwindow,
    key: string,
    scancode: number,
    action: number,
    mod: number
  ) => void
) => void;
declare const CXX_glfwSetCharCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, value: number) => void
) => void;
declare const CXX_glfwSetCharModsCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, mod: number, value: number) => void
) => void;
declare const CXX_glfwSetCursorEnterCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, value: number) => void
) => void;
declare const CXX_glfwSetCursorPosCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, x: number, y: number) => void
) => void;
declare const CXX_glfwSetDropCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, files: string[]) => void
) => void;
declare const CXX_glfwSetErrorCallback: (
  callback?: (id: number, desc: string) => void
) => void;
declare const CXX_glfwSetFramebufferSizeCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, width: number, height: number) => void
) => void;
declare const CXX_glfwSetJoystickCallback: (
  callback?: (jid: number, event: number) => void
) => void;
declare const CXX_glfwSetMonitorCallback: (
  callback?: (monitor: GLFWmonitor, event: number) => void
) => void;
declare const CXX_glfwSetMouseButtonCallback: (
  win: GLFWwindow,
  callback?: (
    win: GLFWwindow,
    button: number,
    action: number,
    mod: number
  ) => void
) => void;
declare const CXX_glfwSetScrollCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, x: number, y: number) => void
) => void;
declare const CXX_glfwSetWindowCloseCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow) => void
) => void;
declare const CXX_glfwSetWindowContentScaleCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, dx: number, dy: number) => void
) => void;
declare const CXX_glfwSetWindowFocusCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, event: number) => void
) => void;
declare const CXX_glfwSetWindowIconifyCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, event: number) => void
) => void;
declare const CXX_glfwSetWindowMaximizeCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, event: number) => void
) => void;
declare const CXX_glfwSetWindowPosCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, x: number, y: number) => void
) => void;
declare const CXX_glfwSetWindowRefreshCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow) => void
) => void;
declare const CXX_glfwSetWindowSizeCallback: (
  win: GLFWwindow,
  callback?: (win: GLFWwindow, w: number, h: number) => void
) => void;
declare const CXX_createImage: (
  width: number,
  height: number,
  buf: Int32Array
) => GLFWimage;
declare const CXX_deleteImage: (img: GLFWimage) => void;
export {
  Long,
  Point,
  Size,
  Scale,
  Rect,
  Workarea,
  VideoMode,
  GamepadState,
  GammaRamp,
  GLFWwindow,
  GLFWmonitor,
  CXX_glfwInit,
  CXX_glfwTerminate,
  CXX_glfwCreateWindow,
  CXX_glfwPollEvents,
  CXX_glfwWindowShouldClose,
  CXX_glfwGetKey,
  CXX_glfwGetMouseButton,
  CXX_glfwGetClipboardString,
  CXX_glfwGetCurrentContext,
  CXX_glfwGetCursorPos,
  CXX_glfwGetError,
  CXX_glfwGetFramebufferSize,
  CXX_glfwGetGamepadName,
  CXX_glfwGetGamepadState,
  CXX_glfwGetGammaRamp,
  CXX_glfwGetInputMode,
  CXX_glfwGetJoystickAxes,
  CXX_glfwGetJoystickButtons,
  CXX_glfwGetJoystickGUID,
  CXX_glfwGetJoystickHats,
  CXX_glfwGetJoystickName,
  CXX_glfwGetKeyName,
  CXX_glfwGetKeyScancode,
  CXX_glfwGetMonitorContentScale,
  CXX_glfwGetMonitorName,
  CXX_glfwGetMonitorPhysicalSize,
  CXX_glfwGetMonitorPos,
  CXX_glfwGetMonitors,
  CXX_glfwGetMonitorWorkarea,
  CXX_glfwGetPrimaryMonitor,
  CXX_glfwGetProcAddress,
  CXX_glfwGetRequiredInstanceExtensions,
  CXX_glfwGetTime,
  CXX_glfwGetTimerFrequency,
  CXX_glfwGetTimerValue,
  CXX_glfwGetVersion,
  CXX_glfwGetVersionString,
  CXX_glfwGetVideoMode,
  CXX_glfwGetVideoModes,
  CXX_glfwGetWindowAttrib,
  CXX_glfwGetWindowContentScale,
  CXX_glfwGetWindowFrameSize,
  CXX_glfwGetWindowMonitor,
  CXX_glfwGetWindowOpacity,
  CXX_glfwGetWindowPos,
  CXX_glfwGetWindowSize,
  CXX_glfwSetKeyCallback,
  CXX_glfwCreateCursor,
  CXX_glfwCreateStandardCursor,
  CXX_glfwDefaultWindowHints,
  CXX_glfwDestroyCursor,
  CXX_glfwDestroyWindow,
  CXX_glfwExtensionSupported,
  CXX_glfwFocusWindow,
  CXX_glfwHideWindow,
  CXX_glfwIconifyWindow,
  CXX_glfwInitHint,
  CXX_glfwJoystickIsGamepad,
  CXX_glfwJoystickPresent,
  CXX_glfwMakeContextCurrent,
  CXX_glfwMaximizeWindow,
  CXX_glfwPostEmptyEvent,
  CXX_glfwRawMouseMotionSupported,
  CXX_glfwRequestWindowAttention,
  CXX_glfwRestoreWindow,
  CXX_glfwSetClipboardString,
  CXX_glfwSetCursor,
  CXX_glfwSetCursorPos,
  CXX_glfwSetGamma,
  CXX_glfwSetGammaRamp,
  CXX_glfwSetInputMode,
  CXX_glfwSetWindowAspectRatio,
  CXX_glfwSetWindowAttrib,
  CXX_glfwSetWindowIcon,
  CXX_glfwSetWindowMonitor,
  CXX_glfwSetWindowOpacity,
  CXX_glfwSetWindowPos,
  CXX_glfwSetWindowShouldClose,
  CXX_glfwSetWindowSize,
  CXX_glfwSetWindowSizeLimits,
  CXX_glfwSetWindowTitle,
  CXX_glfwShowWindow,
  CXX_glfwSwapBuffers,
  CXX_glfwSwapInterval,
  CXX_glfwUpdateGamepadMappings,
  CXX_glfwVulkanSupported,
  CXX_glfwWaitEvents,
  CXX_glfwWaitEventsTimeout,
  CXX_glfwWindowHint,
  CXX_glfwWindowHintString,
  CXX_glfwSetCharCallback,
  CXX_glfwSetCharModsCallback,
  CXX_glfwSetCursorEnterCallback,
  CXX_glfwSetCursorPosCallback,
  CXX_glfwSetDropCallback,
  CXX_glfwSetErrorCallback,
  CXX_glfwSetFramebufferSizeCallback,
  CXX_glfwSetJoystickCallback,
  CXX_glfwSetMonitorCallback,
  CXX_glfwSetMouseButtonCallback,
  CXX_glfwSetScrollCallback,
  CXX_glfwSetWindowCloseCallback,
  CXX_glfwSetWindowContentScaleCallback,
  CXX_glfwSetWindowFocusCallback,
  CXX_glfwSetWindowIconifyCallback,
  CXX_glfwSetWindowMaximizeCallback,
  CXX_glfwSetWindowPosCallback,
  CXX_glfwSetWindowRefreshCallback,
  CXX_glfwSetWindowSizeCallback,
  CXX_createImage,
  CXX_deleteImage,
};
