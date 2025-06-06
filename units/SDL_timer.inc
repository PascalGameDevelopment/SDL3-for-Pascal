{
  This file is part of:

    SDL3 for Pascal
    (https://github.com/PascalGameDevelopment/SDL3-for-Pascal)
    SPDX-License-Identifier: Zlib
}

{*
 * # CategoryTimer
 *
 * SDL time management routines.
  }

{ SDL time constants  }

const
  SDL_MS_PER_SECOND = 1000;
  SDL_US_PER_SECOND = 1000000;
  SDL_NS_PER_SECOND = 1000000000;
  SDL_NS_PER_MS = 1000000;
  SDL_NS_PER_US = 1000;
function SDL_SECONDS_TO_NS(S: Integer): Integer;
function SDL_NS_TO_SECONDS(NS: Integer): Integer;
function SDL_MS_TO_NS(MS: Integer): Integer;
function SDL_NS_TO_MS(NS: Integer): Integer;
function SDL_US_TO_NS(US: Integer): Integer;
function SDL_NS_TO_US(NS: Integer): Integer;

{*
 * Get the number of milliseconds since SDL library initialization.
 *
 * \returns an unsigned 64-bit value representing the number of milliseconds
 *          since the SDL library initialized.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
  }
function SDL_GetTicks: cuint64; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetTicks' {$ENDIF} {$ENDIF};

{*
 * Get the number of nanoseconds since SDL library initialization.
 *
 * \returns an unsigned 64-bit value representing the number of nanoseconds
 *          since the SDL library initialized.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
  }
function SDL_GetTicksNS: cuint64; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetTicksNS' {$ENDIF} {$ENDIF};

{*
 * Get the current value of the high resolution counter.
 *
 * This function is typically used for profiling.
 *
 * The counter values are only meaningful relative to each other. Differences
 * between values can be converted to times by using
 * SDL_GetPerformanceFrequency().
 *
 * \returns the current counter value.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_GetPerformanceFrequency
  }
function SDL_GetPerformanceCounter: cuint64; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetPerformanceCounter' {$ENDIF} {$ENDIF};

{*
 * Get the count per second of the high resolution counter.
 *
 * \returns a platform-specific count per second.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_GetPerformanceCounter
  }
function SDL_GetPerformanceFrequency: cuint64; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_GetPerformanceFrequency' {$ENDIF} {$ENDIF};

{*
 * Wait a specified number of milliseconds before returning.
 *
 * This function waits a specified number of milliseconds before returning. It
 * waits at least the specified time, but possibly longer due to OS
 * scheduling.
 *
 * \param ms the number of milliseconds to delay.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
  }
procedure SDL_Delay(ms: cuint32); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_Delay' {$ENDIF} {$ENDIF};

{*
 * Wait a specified number of nanoseconds before returning.
 *
 * This function waits a specified number of nanoseconds before returning. It
 * waits at least the specified time, but possibly longer due to OS
 * scheduling.
 *
 * \param ns the number of nanoseconds to delay.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
  }
procedure SDL_DelayNS(ns: cuint64); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_DelayNS' {$ENDIF} {$ENDIF};

{*
 * Wait a specified number of nanoseconds before returning.
 *
 * This function waits a specified number of nanoseconds before returning. It
 * will attempt to wait as close to the requested time as possible, busy
 * waiting if necessary, but could return later due to OS scheduling.
 *
 * \param ns the number of nanoseconds to delay.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.2.0.
  }
procedure SDL_DelayPrecise(ns: cuint64); cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_DelayPrecise' {$ENDIF} {$ENDIF};

{*
 * Definition of the timer ID type.
 *
 * \since This datatype is available since SDL 3.1.3.
  }
type
  PPSDL_TimerID = ^PSDL_TimerID;
  PSDL_TimerID = ^TSDL_TimerID;
  TSDL_TimerID = cuint32;

{*
 * Function prototype for the millisecond timer callback function.
 *
 * The callback function is passed the current timer interval and returns the
 * next timer interval, in milliseconds. If the returned value is the same as
 * the one passed in, the periodic alarm continues, otherwise a new alarm is
 * scheduled. If the callback returns 0, the periodic alarm is canceled and
 * will be removed.
 *
 * \param userdata an arbitrary Pointer provided by the app through
 *                 SDL_AddTimer, for its own use.
 * \param timerID the current timer being processed.
 * \param interval the current callback time interval.
 * \returns the new callback time interval, or 0 to disable further runs of
 *          the callback.
 *
 * \threadsafety SDL may call this callback at any time from a background
 *               thread; the application is responsible for locking resources
 *               the callback touches that need to be protected.
 *
 * \since This datatype is available since SDL 3.1.3.
 *
 * \sa SDL_AddTimer
  }
type
  TSDL_TimerCallback = function (userdata: Pointer; timerID: TSDL_TimerID; interval: cuint32): cuint32; cdecl;

{*
 * Call a callback function at a future time.
 *
 * The callback function is passed the current timer interval and the user
 * supplied parameter from the SDL_AddTimer() call and should return the next
 * timer interval. If the value returned from the callback is 0, the timer is
 * canceled and will be removed.
 *
 * The callback is run on a separate thread, and for short timeouts can
 * potentially be called before this function returns.
 *
 * Timers take into account the amount of time it took to execute the
 * callback. For example, if the callback took 250 ms to execute and returned
 * 1000 (ms), the timer would only wait another 750 ms before its next
 * iteration.
 *
 * Timing may be inexact due to OS scheduling. Be sure to note the current
 * time with SDL_GetTicksNS() or SDL_GetPerformanceCounter() in case your
 * callback needs to adjust for variances.
 *
 * \param interval the timer delay, in milliseconds, passed to `callback`.
 * \param callback the SDL_TimerCallback function to call when the specified
 *                 `interval` elapses.
 * \param userdata a Pointer that is passed to `callback`.
 * \returns a timer ID or 0 on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_AddTimerNS
 * \sa SDL_RemoveTimer
  }
function SDL_AddTimer(interval: cuint32; callback: TSDL_TimerCallback; userdata: Pointer): TSDL_TimerID; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_AddTimer' {$ENDIF} {$ENDIF};

{*
 * Function prototype for the nanosecond timer callback function.
 *
 * The callback function is passed the current timer interval and returns the
 * next timer interval, in nanoseconds. If the returned value is the same as
 * the one passed in, the periodic alarm continues, otherwise a new alarm is
 * scheduled. If the callback returns 0, the periodic alarm is canceled and
 * will be removed.
 *
 * \param userdata an arbitrary Pointer provided by the app through
 *                 SDL_AddTimer, for its own use.
 * \param timerID the current timer being processed.
 * \param interval the current callback time interval.
 * \returns the new callback time interval, or 0 to disable further runs of
 *          the callback.
 *
 * \threadsafety SDL may call this callback at any time from a background
 *               thread; the application is responsible for locking resources
 *               the callback touches that need to be protected.
 *
 * \since This datatype is available since SDL 3.1.3.
 *
 * \sa SDL_AddTimerNS
  }
type
  TSDL_NSTimerCallback = function (userdata: Pointer; timerID: TSDL_TimerID; interval: cuint64): cuint64; cdecl;

{*
 * Call a callback function at a future time.
 *
 * The callback function is passed the current timer interval and the user
 * supplied parameter from the SDL_AddTimerNS() call and should return the
 * next timer interval. If the value returned from the callback is 0, the
 * timer is canceled and will be removed.
 *
 * The callback is run on a separate thread, and for short timeouts can
 * potentially be called before this function returns.
 *
 * Timers take into account the amount of time it took to execute the
 * callback. For example, if the callback took 250 ns to execute and returned
 * 1000 (ns), the timer would only wait another 750 ns before its next
 * iteration.
 *
 * Timing may be inexact due to OS scheduling. Be sure to note the current
 * time with SDL_GetTicksNS() or SDL_GetPerformanceCounter() in case your
 * callback needs to adjust for variances.
 *
 * \param interval the timer delay, in nanoseconds, passed to `callback`.
 * \param callback the SDL_TimerCallback function to call when the specified
 *                 `interval` elapses.
 * \param userdata a Pointer that is passed to `callback`.
 * \returns a timer ID or 0 on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_AddTimer
 * \sa SDL_RemoveTimer
  }
function SDL_AddTimerNS(interval: cuint64; callback: TSDL_NSTimerCallback; userdata: Pointer): TSDL_TimerID; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_AddTimerNS' {$ENDIF} {$ENDIF};

{*
 * Remove a timer created with SDL_AddTimer().
 *
 * \param id the ID of the timer to remove.
 * \returns true on success or false on failure; call SDL_GetError() for more
 *          information.
 *
 * \threadsafety It is safe to call this function from any thread.
 *
 * \since This function is available since SDL 3.1.3.
 *
 * \sa SDL_AddTimer
  }
function SDL_RemoveTimer(id: TSDL_TimerID): Boolean; cdecl;
  external SDL_LibName {$IFDEF DELPHI} {$IFDEF MACOS} name '_SDL_RemoveTimer' {$ENDIF} {$ENDIF};

