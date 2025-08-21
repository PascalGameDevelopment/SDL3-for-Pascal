#!/bin/bash

set -eu -o pipefail

if [ -t 1 ]; then
	ANSI_BOLD="$(printf "\x1b[1m")"
	ANSI_GREEN="$(printf "\x1b[32m")"
	ANSI_RED="$(printf "\x1b[31m")"
	ANSI_RESET="$(printf "\x1b[0m")"
else
	ANSI_BOLD=""
	ANSI_GREEN=""
	ANSI_RED=""
	ANSI_RESET=""
fi

# -- cd to script directory

cd "$(dirname "${0}")"
SDL_UNITS_PATH="$(pwd)/../units/"

TEMP_DIR="$(mktemp --directory)"
PASCAL_SOURCE="${TEMP_DIR}/test.pas"
C_SOURCE="${TEMP_DIR}/test.c"

# -- generate sources

cat > "${PASCAL_SOURCE}" << EOF
program test;

uses
	SDL3;

Begin
EOF

cat > "${C_SOURCE}" << EOF
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <SDL3/SDL.h>

int main(void) {
EOF

for TYPENAME in \
	SDL_AppResult \
	SDL_ArrayOrder \
	SDL_AudioDeviceEvent \
	SDL_AudioDeviceID \
	SDL_AudioFormat \
	SDL_AudioSpec \
	SDL_BitmapOrder \
	SDL_BlendFactor \
	SDL_BlendMode \
	SDL_BlendOperation \
	SDL_CameraDeviceEvent \
	SDL_CameraID \
	SDL_CameraPosition \
	SDL_CameraSpec \
	SDL_Capitalization \
	SDL_ChromaLocation \
	SDL_ClipboardEvent \
	SDL_Color \
	SDL_ColorPrimaries \
	SDL_ColorRange \
	SDL_Colorspace \
	SDL_ColorType \
	SDL_CommonEvent \
	SDL_DateTime \
	SDL_DialogFileFilter \
	SDL_DisplayEvent \
	SDL_DisplayID \
	SDL_DisplayMode \
	SDL_DisplayOrientation \
	SDL_DropEvent \
	SDL_EnumerationResult \
	SDL_Event \
	SDL_EventAction \
	SDL_EventType \
	SDL_FColor \
	SDL_FileDialogType \
	SDL_Finger \
	SDL_FingerID \
	SDL_FlashOperation \
	SDL_FlipMode \
	SDL_Folder \
	SDL_FPoint \
	SDL_FRect \
	SDL_GamepadAxis \
	SDL_GamepadAxisEvent \
	SDL_GamepadBinding \
	SDL_GamepadBindingType \
	SDL_GamepadButton \
	SDL_GamepadButtonEvent \
	SDL_GamepadButtonLabel \
	SDL_GamepadDeviceEvent \
	SDL_GamepadSensorEvent \
	SDL_GamepadTouchpadEvent \
	SDL_GamepadType \
	SDL_GlobFlags \
	SDL_HapticCondition \
	SDL_HapticConstant \
	SDL_HapticCustom \
	SDL_HapticDirection \
	SDL_HapticEffect \
	SDL_HapticID \
	SDL_HapticLeftRight \
	SDL_HapticPeriodic \
	SDL_HapticRamp \
	SDL_HintPriority \
	SDL_HitTestResult \
	SDL_InitFlags \
	SDL_JoyAxisEvent \
	SDL_JoyBallEvent \
	SDL_JoyBatteryEvent \
	SDL_JoyButtonEvent \
	SDL_JoyDeviceEvent \
	SDL_JoyHatEvent \
	SDL_JoystickConnectionState \
	SDL_JoystickID \
	SDL_JoystickType \
	SDL_KeyboardDeviceEvent \
	SDL_KeyboardEvent \
	SDL_KeyboardID \
	SDL_Keycode \
	SDL_Keymod \
	SDL_Locale \
	SDL_LogCategory \
	SDL_LogPriority \
	SDL_MatrixCoefficients \
	SDL_MessageBoxButtonFlags \
	SDL_MessageBoxColorType \
	SDL_MessageBoxFlags \
	SDL_MouseButtonEvent \
	SDL_MouseButtonFlags \
	SDL_MouseDeviceEvent \
	SDL_MouseID \
	SDL_MouseMotionEvent \
	SDL_MouseWheelDirection \
	SDL_MouseWheelEvent \
	SDL_Palette \
	SDL_PackedLayout \
	SDL_PackedOrder \
	SDL_PathInfo \
	SDL_PathType \
	SDL_PenAxis \
	SDL_PenAxisEvent \
	SDL_PenButtonEvent \
	SDL_PenID \
	SDL_PenInputFlags \
	SDL_PenMotionEvent \
	SDL_PenProximityEvent \
	SDL_PenTouchEvent \
	SDL_PixelFormat \
	SDL_PixelFormatDetails \
	SDL_PixelType \
	SDL_Point \
	SDL_PowerState \
	SDL_PropertiesID \
	SDL_PropertyType \
	SDL_QuitEvent \
	SDL_Rect \
	SDL_RendererLogicalPresentation \
	SDL_RenderEvent \
	SDL_ScaleMode \
	SDL_Scancode \
	SDL_SensorEvent \
	SDL_SensorID \
	SDL_SensorType \
	SDL_SurfaceFlags \
	SDL_SystemCursor \
	SDL_SystemTheme \
	SDL_TextEditingEvent \
	SDL_TextEditingCandidatesEvent \
	SDL_TextInputEvent \
	SDL_TextInputType \
	SDL_TextureAccess \
	SDL_ThreadID \
	SDL_ThreadPriority \
	SDL_ThreadState \
	SDL_TimeFormat \
	SDL_TimerID \
	SDL_TouchDeviceType \
	SDL_TouchFingerEvent \
	SDL_TouchID \
	SDL_TransferCharacteristics \
	SDL_TrayEntryFlags \
	SDL_UserEvent \
	SDL_Vertex \
	SDL_VirtualJoystickDesc \
	SDL_VirtualJoystickSensorDesc \
	SDL_VirtualJoystickTouchpadDesc \
	SDL_WindowEvent \
	SDL_WindowFlags \
	SDL_WindowID \
; do
	echo $'\t'"Writeln('${TYPENAME}: ', SizeOf(T${TYPENAME}));" >> "${PASCAL_SOURCE}"
	echo $'\t'"printf(\"${TYPENAME}: %zu\n\", sizeof(${TYPENAME}));" >> "${C_SOURCE}"
done

echo "End." >> "${PASCAL_SOURCE}"
echo $'\t'"return 0;"$'\n'"}" >> "${C_SOURCE}"

# -- sources generated

PASCAL_BINARY="${TEMP_DIR}/pascal"
C_BINARY="${TEMP_DIR}/c"

fpc -v0e "-Fu${SDL_UNITS_PATH}" "-o${PASCAL_BINARY}" "${PASCAL_SOURCE}"
gcc -std=c23 -Wall -Wpedantic -Werror -o "${C_BINARY}" "${C_SOURCE}"

# -- programs compiled

PASCAL_OUTPUT="${TEMP_DIR}/result-pas.txt"
C_OUTPUT="${TEMP_DIR}/result-c.txt"

"${PASCAL_BINARY}" > "${PASCAL_OUTPUT}"
"${C_BINARY}" > "${C_OUTPUT}"
pr -mt <(echo "-- Pascal --"; cat "${PASCAL_OUTPUT}") <(echo "-- C --"; cat "${C_OUTPUT}")

set +e
DIFF="$(diff --width=80 --suppress-common-lines --side-by-side "${PASCAL_OUTPUT}" "${C_OUTPUT}")"
EXIT_CODE="${?}"

echo ""
if [ "${EXIT_CODE}" -eq 0 ]; then
	echo "${ANSI_BOLD}[${ANSI_GREEN}PASS${ANSI_RESET}${ANSI_BOLD}]${ANSI_RESET} Outputs match"
else
	echo "${ANSI_BOLD}[${ANSI_RED}FAIL${ANSI_RESET}${ANSI_BOLD}]${ANSI_RESET} Outputs differ!"
	echo "${DIFF}"
fi

rm -rf "${TEMP_DIR}"
exit "${EXIT_CODE}"
