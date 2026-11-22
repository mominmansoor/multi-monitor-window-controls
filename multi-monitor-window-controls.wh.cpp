// ==WindhawkMod==
// @id              multi-monitor-window-controls
// @name            Multi-Monitor Window Controls
// @description     Keyboard shortcuts to minimize and restore windows one at a time, jump focus between monitors with an outline flash, and move windows between monitors
// @version         2.0.0
// @author          Momin
// @github          https://github.com/mominmansoor
// @include         windhawk.exe
// @compilerOptions -luser32 -lgdi32 -lshcore -ldwmapi
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Multi-Monitor Window Controls

Keyboard control over windows on a multi-monitor setup. Every shortcut can be
changed or turned off in the mod settings.

## Default shortcuts

| Shortcut | What it does |
|---|---|
| Right Ctrl + Down | Minimize the top window on the active monitor, so the one under it shows. Press again for the next one. |
| Right Ctrl + Up | Bring back the last window minimized this way, on top. One per press. |
| Double tap Right Shift | Switch keyboard focus to the next monitor. |
| Right Ctrl + Right Shift + Up / Down | Switch keyboard focus to the next / previous monitor. |
| Right Ctrl + Left / Right | Move the active window to the monitor on that side. |
| Right Ctrl + Right Shift + Left / Right | Move all windows on the active monitor to the monitor on that side. |

When focus switches, a short outline flashes around the monitor that got it.
Its color, opacity and width are settings, and it can be turned off.

## Details

- **Minimize and restore** work like a stack: the windows come back in the
  reverse order they were minimized. Windows closed or restored by hand in the
  meantime are skipped.
- **Focus switching** gives focus to the top window on the next monitor (left
  to right, wrapping around). Monitors with no windows are skipped. A double
  tap only counts if the key is tapped twice quickly with nothing else pressed
  in between, so typing capital letters doesn't trigger it.
- **Moving a window**: maximized and borderless fullscreen windows stay that
  way on the new monitor. Other windows keep their size (scaled for the
  monitor's DPI), shrink to fit if needed, and are centered. When moving all
  windows, each window keeps its relative position instead, and focus stays on
  the window that had it.
- Left / Right pick the nearest monitor whose center is on that side.

## Similar mods

[Move Window to Monitor](https://windhawk.net/mods/move-window-to-monitor),
[Move and Gather Windows](https://windhawk.net/mods/gather-windows-to-monitor)
and [Snap Commander](https://windhawk.net/mods/snap-commander) can also move
windows between monitors. If that's all you need, use one of them. This mod is
built around the parts they don't have: minimizing and restoring windows one at
a time, and switching keyboard focus between monitors (including a double tap
key) with a visible outline. Moving windows is included so all multi-monitor
shortcuts can share one modifier key, such as Right Ctrl alone.

The move logic started from Move Window to Monitor by TomberWolf. Thanks also
to sultansaad-dev.

## Notes

- The mod uses a low-level keyboard hook, because RegisterHotKey can't tell
  Right Ctrl from Left Ctrl or detect a double tap. A key press is only blocked
  when it matches a shortcut **and** that shortcut has something to do (for
  example, Right Ctrl + Left passes through to the app when there's no monitor
  on the left). Nothing is recorded or sent anywhere.
- Windows doesn't let normal programs control windows running as
  administrator (for example Task Manager), so shortcuts do nothing on those.
- When a shortcut uses Alt, the mod sends an unassigned key (0xE8) so the
  app's menu bar doesn't open when you release Alt.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- moveWindowLeft:
  - key: Left
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: none
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Move window to the monitor on the left
- moveWindowRight:
  - key: Right
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: none
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Move window to the monitor on the right
- moveAllLeft:
  - key: Left
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: rshift
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Move all windows to the monitor on the left
- moveAllRight:
  - key: Right
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: rshift
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Move all windows to the monitor on the right
- minimizeTop:
  - key: Down
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: none
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Minimize the top window
- restoreMinimized:
  - key: Up
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: none
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Restore the last minimized window
- focusNext:
  - key: Up
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: rshift
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Switch focus to the next monitor
- focusPrevious:
  - key: Down
    $name: Key
    $description: >-
      A letter, a digit, Left, Right, Up, Down, PageUp, PageDown, Home, End,
      Insert, Delete, Space, Tab, Enter, Backspace, Escape, F1 to F24 or
      Numpad0 to Numpad9. Leave empty to turn this shortcut off.
  - modifier: rctrl
    $name: Modifier
    $options:
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  - extraModifier: rshift
    $name: Second modifier
    $options:
    - none: None
    - rctrl: Right Ctrl
    - lctrl: Left Ctrl
    - ctrl: Ctrl (either side)
    - ralt: Right Alt
    - lalt: Left Alt
    - alt: Alt (either side)
    - rshift: Right Shift
    - lshift: Left Shift
    - shift: Shift (either side)
  $name: Switch focus to the previous monitor
- doubleTapKey: rshift
  $name: Double tap to switch monitor focus
  $description: >-
    Tap this key twice quickly to switch focus to the next monitor. Turn it
    off if an app you use has its own double tap, for example double Shift in
    JetBrains IDEs.
  $options:
  - none: "Off"
  - rshift: Right Shift
  - lshift: Left Shift
  - rctrl: Right Ctrl
  - lctrl: Left Ctrl
  - ralt: Right Alt
  - lalt: Left Alt
- focusOutline:
  - enabled: true
    $name: Flash an outline when focus switches
  - color: white
    $name: Color
    $options:
    - white: White
    - red: Red
    - orange: Orange
    - yellow: Yellow
    - lime: Lime
    - green: Green
    - cyan: Cyan
    - blue: Blue
    - purple: Purple
    - pink: Pink
    - black: Black
  - opacity: 100
    $name: Opacity (%)
    $description: From 10 (faint) to 100 (solid).
  - width: 3
    $name: Width
    $description: >-
      Thickness at 100% display scaling, scaled up on high DPI monitors.
      Recommended 1 to 5.
  $name: Focus outline
*/
// ==/WindhawkModSettings==

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <dwmapi.h>
#include <shellscalingapi.h>
#include <windhawk_utils.h>

#include <algorithm>
#include <atomic>
#include <cwctype>
#include <vector>

#ifndef WPF_ASYNCWINDOWPLACEMENT
#define WPF_ASYNCWINDOWPLACEMENT 0x0004
#endif

// ── settings ──────────────────────────────────────────────────────────────────

enum Action {
    kMoveWindowLeft,
    kMoveWindowRight,
    kMoveAllLeft,
    kMoveAllRight,
    kMinimizeTop,
    kRestoreMinimized,
    kFocusNext,
    kFocusPrevious,
    kActionCount,
};

static const PCWSTR kActionSettingNames[kActionCount] = {
    L"moveWindowLeft", L"moveWindowRight",  L"moveAllLeft", L"moveAllRight",
    L"minimizeTop",    L"restoreMinimized", L"focusNext",   L"focusPrevious",
};

// Which side(s) of a modifier family (Ctrl, Shift, Alt) must be held.
enum Side : BYTE { kNone, kLeft, kRight, kEither, kBoth };

struct Shortcut {
    UINT vk = 0;  // 0 = shortcut off
    BYTE ctrl = kNone;
    BYTE shift = kNone;
    BYTE alt = kNone;
};

struct Settings {
    Shortcut shortcuts[kActionCount];
    UINT doubleTapVk = 0;  // 0 = off
    bool outlineEnabled = true;
    COLORREF outlineColor = RGB(255, 255, 255);
    BYTE outlineAlpha = 255;
    int outlineWidth = 3;
};

// Everything below runs on the mod's single worker thread (the keyboard hook,
// the window procedures and the actions), so no locking is needed.
static Settings g_settings;

static void AddModifier(Shortcut& s, PCWSTR name) {
    static const struct {
        PCWSTR name;
        int family;
        BYTE side;
    } table[] = {
        {L"lctrl", 0, kLeft},  {L"rctrl", 0, kRight},  {L"ctrl", 0, kEither},
        {L"lshift", 1, kLeft}, {L"rshift", 1, kRight}, {L"shift", 1, kEither},
        {L"lalt", 2, kLeft},   {L"ralt", 2, kRight},   {L"alt", 2, kEither},
    };
    for (const auto& e : table) {
        if (wcscmp(name, e.name) != 0) continue;
        BYTE& f = e.family == 0 ? s.ctrl : e.family == 1 ? s.shift : s.alt;
        if (f == kNone || f == e.side) {
            f = e.side;
        } else if (f == kEither || e.side == kEither) {
            f = kEither;
        } else {
            f = kBoth;  // left and right of the same family
        }
        return;
    }
}

static UINT ParseKey(PCWSTR name) {
    if (!name[0]) return 0;

    if (!name[1]) {
        const wchar_t c = towupper(name[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
    }

    static const struct {
        PCWSTR name;
        UINT vk;
    } named[] = {
        {L"Left", VK_LEFT},       {L"Right", VK_RIGHT},
        {L"Up", VK_UP},           {L"Down", VK_DOWN},
        {L"PageUp", VK_PRIOR},    {L"PageDown", VK_NEXT},
        {L"Home", VK_HOME},       {L"End", VK_END},
        {L"Insert", VK_INSERT},   {L"Delete", VK_DELETE},
        {L"Space", VK_SPACE},     {L"Tab", VK_TAB},
        {L"Enter", VK_RETURN},    {L"Backspace", VK_BACK},
        {L"Escape", VK_ESCAPE},
    };
    for (const auto& k : named) {
        if (_wcsicmp(name, k.name) == 0) return k.vk;
    }

    if ((name[0] == L'F' || name[0] == L'f') && iswdigit(name[1])) {
        const int n = _wtoi(name + 1);
        if (n >= 1 && n <= 24) return VK_F1 + n - 1;
    }

    if (_wcsnicmp(name, L"Numpad", 6) == 0 && iswdigit(name[6]) && !name[7]) {
        return VK_NUMPAD0 + (name[6] - L'0');
    }

    Wh_Log(L"Unknown key name \"%ls\"", name);
    return 0;
}

static void LoadSettings() {
    using WindhawkUtils::StringSetting;
    Settings s;

    for (int i = 0; i < kActionCount; i++) {
        const PCWSTR id = kActionSettingNames[i];
        Shortcut& sc = s.shortcuts[i];
        sc.vk = ParseKey(StringSetting::make(L"%ls.key", id));
        AddModifier(sc, StringSetting::make(L"%ls.modifier", id));
        AddModifier(sc, StringSetting::make(L"%ls.extraModifier", id));
    }

    static const struct {
        PCWSTR name;
        UINT vk;
    } tapKeys[] = {
        {L"rshift", VK_RSHIFT},  {L"lshift", VK_LSHIFT}, {L"rctrl", VK_RCONTROL},
        {L"lctrl", VK_LCONTROL}, {L"ralt", VK_RMENU},    {L"lalt", VK_LMENU},
    };
    StringSetting tap = StringSetting::make(L"doubleTapKey");
    for (const auto& t : tapKeys) {
        if (wcscmp(tap, t.name) == 0) s.doubleTapVk = t.vk;
    }

    static const struct {
        PCWSTR name;
        COLORREF color;
    } colors[] = {
        {L"white", RGB(255, 255, 255)}, {L"red", RGB(255, 40, 40)},
        {L"orange", RGB(255, 140, 0)},  {L"yellow", RGB(255, 230, 0)},
        {L"lime", RGB(160, 255, 0)},    {L"green", RGB(0, 200, 70)},
        {L"cyan", RGB(0, 230, 255)},    {L"blue", RGB(40, 100, 255)},
        {L"purple", RGB(160, 70, 255)}, {L"pink", RGB(255, 100, 190)},
        {L"black", RGB(0, 0, 0)},
    };
    s.outlineEnabled = Wh_GetIntSetting(L"focusOutline.enabled") != 0;
    StringSetting color = StringSetting::make(L"focusOutline.color");
    for (const auto& c : colors) {
        if (wcscmp(color, c.name) == 0) s.outlineColor = c.color;
    }
    const int opacity =
        std::clamp(Wh_GetIntSetting(L"focusOutline.opacity"), 10, 100);
    s.outlineAlpha = (BYTE)(255 * opacity / 100);
    s.outlineWidth = std::clamp(Wh_GetIntSetting(L"focusOutline.width"), 1, 20);

    g_settings = s;
}

// ── monitors ──────────────────────────────────────────────────────────────────

struct MonitorInfo {
    HMONITOR hMon;
    RECT rcMon;
    RECT rcWork;
    UINT dpi;
};

// Sorted left to right, then top to bottom. Refreshed before every action and
// when the display layout changes, so the keyboard hook can check it cheaply.
static std::vector<MonitorInfo> g_monitors;

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC, LPRECT, LPARAM) {
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfo(hMon, &mi)) return TRUE;
    UINT dpiX = 96, dpiY = 96;
    if (FAILED(GetDpiForMonitor(hMon, MDT_EFFECTIVE_DPI, &dpiX, &dpiY))) {
        dpiX = 96;
    }
    g_monitors.push_back({hMon, mi.rcMonitor, mi.rcWork, dpiX});
    return TRUE;
}

static void RefreshMonitors() {
    g_monitors.clear();
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, 0);
    std::sort(g_monitors.begin(), g_monitors.end(),
              [](const MonitorInfo& a, const MonitorInfo& b) {
                  if (a.rcMon.left != b.rcMon.left)
                      return a.rcMon.left < b.rcMon.left;
                  return a.rcMon.top < b.rcMon.top;
              });
}

static int FindMonitorIndex(HMONITOR hMon) {
    for (int i = 0; i < (int)g_monitors.size(); i++) {
        if (g_monitors[i].hMon == hMon) return i;
    }
    return -1;
}

// The nearest monitor whose center is to the left (-1) or right (+1) of the
// given monitor's center, or -1 if there is none.
static int FindNeighbor(int cur, int direction) {
    if (cur < 0) return -1;
    const RECT& c = g_monitors[cur].rcMon;
    const int cx = (c.left + c.right) / 2, cy = (c.top + c.bottom) / 2;
    int best = -1, bestScore = 0;
    for (int i = 0; i < (int)g_monitors.size(); i++) {
        const RECT& r = g_monitors[i].rcMon;
        const int dx = (r.left + r.right) / 2 - cx;
        const int dy = (r.top + r.bottom) / 2 - cy;
        if (dx * direction <= 0) continue;
        const int score = abs(dx) + abs(dy);
        if (best < 0 || score < bestScore) {
            best = i;
            bestScore = score;
        }
    }
    return best;
}

// WINDOWPLACEMENT uses workspace coordinates, which are offset from screen
// coordinates by the primary monitor's work area origin.
static POINT GetWorkspaceOffset() {
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfo(MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY),
                        &mi)) {
        return {0, 0};
    }
    return {mi.rcWork.left, mi.rcWork.top};
}

// ── windows ───────────────────────────────────────────────────────────────────

static bool IsShellClass(HWND hwnd) {
    wchar_t cls[64] = {};
    GetClassName(hwnd, cls, ARRAYSIZE(cls));
    return wcscmp(cls, L"Progman") == 0 || wcscmp(cls, L"WorkerW") == 0 ||
           wcscmp(cls, L"Shell_TrayWnd") == 0 ||
           wcscmp(cls, L"Shell_SecondaryTrayWnd") == 0;
}

// Store (UWP) apps such as WhatsApp can report their inner CoreWindow as the
// foreground window. The ApplicationFrameWindow around it is the one that can
// be moved and minimized.
static BOOL CALLBACK FindUwpFrameProc(HWND frame, LPARAM lParam) {
    auto* pair = reinterpret_cast<HWND*>(lParam);  // [0] core, [1] frame
    wchar_t cls[64] = {};
    GetClassName(frame, cls, ARRAYSIZE(cls));
    if (wcscmp(cls, L"ApplicationFrameWindow") == 0 &&
        FindWindowEx(frame, nullptr, L"Windows.UI.Core.CoreWindow", nullptr) ==
            pair[0]) {
        pair[1] = frame;
        return FALSE;
    }
    return TRUE;
}

static HWND GetActiveTopLevelWindow() {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return nullptr;
    hwnd = GetAncestor(hwnd, GA_ROOT);
    if (!hwnd) return nullptr;

    wchar_t cls[64] = {};
    GetClassName(hwnd, cls, ARRAYSIZE(cls));
    if (wcscmp(cls, L"Windows.UI.Core.CoreWindow") == 0) {
        HWND pair[2] = {hwnd, nullptr};
        EnumWindows(FindUwpFrameProc, reinterpret_cast<LPARAM>(pair));
        if (pair[1]) hwnd = pair[1];
    }

    if (!IsWindowVisible(hwnd) || IsIconic(hwnd) || IsShellClass(hwnd)) {
        return nullptr;
    }
    return hwnd;
}

// The monitor of the active window, or the one under the mouse cursor.
static HMONITOR GetSourceMonitor() {
    if (HWND active = GetActiveTopLevelWindow()) {
        return MonitorFromWindow(active, MONITOR_DEFAULTTONEAREST);
    }
    POINT pt;
    if (!GetCursorPos(&pt)) return nullptr;
    return MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
}

static bool IsWindowCloaked(HWND hwnd) {
    // Windows on other virtual desktops (and suspended UWP windows) are cloaked.
    DWORD cloaked = 0;
    return SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked,
                                           sizeof(cloaked))) &&
           cloaked;
}

// A normal, visible app window: not minimized, cloaked, untitled, a tool
// window, the desktop or the taskbar.
static bool IsEligibleWindow(HWND hwnd) {
    if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) return false;
    const LONG_PTR ex = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    if ((ex & WS_EX_TOOLWINDOW) && !(ex & WS_EX_APPWINDOW)) return false;
    if (ex & WS_EX_NOACTIVATE) return false;
    if (GetWindowTextLength(hwnd) == 0) return false;
    if (IsWindowCloaked(hwnd) || IsShellClass(hwnd)) return false;
    return true;
}

struct CollectContext {
    HMONITOR hMon;
    std::vector<HWND> windows;
};

static BOOL CALLBACK CollectWindowsProc(HWND hwnd, LPARAM lParam) {
    auto* ctx = reinterpret_cast<CollectContext*>(lParam);
    if (IsEligibleWindow(hwnd) &&
        MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST) == ctx->hMon) {
        ctx->windows.push_back(hwnd);
    }
    return TRUE;
}

// Eligible windows on a monitor, top to bottom in z-order.
static std::vector<HWND> GetWindowsOnMonitor(HMONITOR hMon) {
    CollectContext ctx{hMon, {}};
    EnumWindows(CollectWindowsProc, reinterpret_cast<LPARAM>(&ctx));
    return ctx.windows;
}

static void ActivateWindow(HWND hwnd) {
    // An empty input event counts as input from this process, which allows it
    // to set the foreground window. It presses no key.
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
}

// ── moving windows ────────────────────────────────────────────────────────────

// All calls are asynchronous, so a hung app can't block the mod.
// bulk: keep the window's relative position and don't activate it.
static void MoveWindowToMonitor(HWND hwnd, const MonitorInfo& src,
                                const MonitorInfo& dst, bool bulk) {
    WINDOWPLACEMENT wp = {sizeof(wp)};
    RECT rcWin;
    if (!GetWindowPlacement(hwnd, &wp) || !GetWindowRect(hwnd, &rcWin)) return;

    const bool maximized = IsZoomed(hwnd) != FALSE;

    // Borderless fullscreen (F11 in a browser, video players): cover the new
    // monitor.
    if (!maximized && EqualRect(&rcWin, &src.rcMon)) {
        SetWindowPos(hwnd, nullptr, dst.rcMon.left, dst.rcMon.top,
                     dst.rcMon.right - dst.rcMon.left,
                     dst.rcMon.bottom - dst.rcMon.top,
                     SWP_NOZORDER | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
        return;
    }

    const int dstW = dst.rcWork.right - dst.rcWork.left;
    const int dstH = dst.rcWork.bottom - dst.rcWork.top;

    // The restored size if maximized, else the current size, scaled for DPI
    // and shrunk to fit.
    const RECT& rcSize = maximized ? wp.rcNormalPosition : rcWin;
    int w = MulDiv(rcSize.right - rcSize.left, dst.dpi, src.dpi);
    int h = MulDiv(rcSize.bottom - rcSize.top, dst.dpi, src.dpi);
    w = std::min(w, dstW);
    h = std::min(h, dstH);

    int x, y;
    if (bulk) {
        // Map the window's center proportionally onto the new work area.
        const int srcW = std::max(1L, src.rcWork.right - src.rcWork.left);
        const int srcH = std::max(1L, src.rcWork.bottom - src.rcWork.top);
        const int cx = (rcWin.left + rcWin.right) / 2 - src.rcWork.left;
        const int cy = (rcWin.top + rcWin.bottom) / 2 - src.rcWork.top;
        x = dst.rcWork.left + MulDiv(cx, dstW, srcW) - w / 2;
        y = dst.rcWork.top + MulDiv(cy, dstH, srcH) - h / 2;
        x = std::clamp(x, (int)dst.rcWork.left, (int)dst.rcWork.right - w);
        y = std::clamp(y, (int)dst.rcWork.top, (int)dst.rcWork.bottom - h);
    } else {
        x = dst.rcWork.left + (dstW - w) / 2;
        y = dst.rcWork.top + (dstH - h) / 2;
    }

    if (maximized) {
        // Put the restored rect on the new monitor, then maximize: Windows
        // maximizes onto the monitor that holds the restored rect.
        const POINT off = GetWorkspaceOffset();
        wp.rcNormalPosition = {x - off.x, y - off.y, x - off.x + w,
                               y - off.y + h};
        wp.flags |= WPF_ASYNCWINDOWPLACEMENT;
        wp.showCmd = bulk ? SW_SHOWNOACTIVATE : SW_SHOWNORMAL;
        SetWindowPlacement(hwnd, &wp);
        wp.showCmd = SW_SHOWMAXIMIZED;
        SetWindowPlacement(hwnd, &wp);
        return;
    }

    // Applied twice: apps that handle DPI changes can resize themselves right
    // after the first move.
    const HWND insertAfter = bulk ? HWND_TOP : nullptr;
    const UINT flags =
        SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS | (bulk ? 0 : SWP_NOZORDER);
    SetWindowPos(hwnd, insertAfter, x, y, w, h, flags);
    SetWindowPos(hwnd, insertAfter, x, y, w, h, flags);
}

static void MoveActiveWindow(int direction) {
    HWND hwnd = GetActiveTopLevelWindow();
    if (!hwnd) return;
    const int src =
        FindMonitorIndex(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST));
    const int dst = FindNeighbor(src, direction);
    if (dst < 0) return;
    Wh_Log(L"Moving the active window from monitor %d to %d", src, dst);
    MoveWindowToMonitor(hwnd, g_monitors[src], g_monitors[dst], false);
}

// Maximizing a window activates it, so after moving all windows focus is given
// back to the window that had it, once the moves have been processed.
static const UINT_PTR kRefocusTimerId = 1;
static const UINT kRefocusDelayMs = 300;
static HWND g_refocusWindow;

static void MoveAllWindows(HWND timerWnd, int direction) {
    const int src = FindMonitorIndex(GetSourceMonitor());
    const int dst = FindNeighbor(src, direction);
    if (dst < 0) return;

    const HWND active = GetActiveTopLevelWindow();
    const auto windows = GetWindowsOnMonitor(g_monitors[src].hMon);
    Wh_Log(L"Moving %d window(s) from monitor %d to %d", (int)windows.size(),
           src, dst);

    // Bottom to top, so the stacking order is kept.
    for (auto it = windows.rbegin(); it != windows.rend(); ++it) {
        MoveWindowToMonitor(*it, g_monitors[src], g_monitors[dst], true);
    }

    if (active) {
        g_refocusWindow = active;
        SetTimer(timerWnd, kRefocusTimerId, kRefocusDelayMs, nullptr);
    }
}

// ── minimize and restore one window at a time ─────────────────────────────────

// Windows minimized by the shortcut, most recent last.
static std::vector<HWND> g_minimizedStack;

static bool HasRestorableWindow() {
    for (HWND hwnd : g_minimizedStack) {
        if (IsWindow(hwnd) && IsIconic(hwnd)) return true;
    }
    return false;
}

static void MinimizeTopWindow() {
    HWND top = GetActiveTopLevelWindow();
    if (!top) return;

    // The next window down on the same monitor gets focus.
    HWND next = nullptr;
    for (HWND hwnd :
         GetWindowsOnMonitor(MonitorFromWindow(top, MONITOR_DEFAULTTONEAREST))) {
        if (hwnd != top) {
            next = hwnd;
            break;
        }
    }

    if (!ShowWindowAsync(top, next ? SW_SHOWMINNOACTIVE : SW_MINIMIZE)) {
        Wh_Log(L"Could not minimize the window (running as administrator?)");
        return;
    }
    g_minimizedStack.push_back(top);
    if (next) ActivateWindow(next);
}

static void RestoreMinimizedWindow() {
    while (!g_minimizedStack.empty()) {
        HWND hwnd = g_minimizedStack.back();
        g_minimizedStack.pop_back();
        // Skip windows closed or restored by hand in the meantime.
        if (!IsWindow(hwnd) || !IsIconic(hwnd)) continue;
        ShowWindowAsync(hwnd, SW_RESTORE);
        ActivateWindow(hwnd);
        return;
    }
}

// ── focus switching and the outline flash ─────────────────────────────────────

static const wchar_t kFlashClass[] = L"WH_MultiMonitorWindowControls_Flash";
static const UINT_PTR kFlashTimerId = 1;
static const int kFlashHoldTicks = 9;   // about 150 ms
static const int kFlashFadeTicks = 15;  // about 250 ms
static const COLORREF kFlashTransparentColor = RGB(1, 2, 3);
static HWND g_flashWindow;
static int g_flashTick;
static int g_flashThickness;

static LRESULT CALLBACK FlashWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                     LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            HBRUSH clear = CreateSolidBrush(kFlashTransparentColor);
            FillRect(dc, &rc, clear);
            DeleteObject(clear);

            const int t = g_flashThickness;
            const RECT edges[] = {
                {rc.left, rc.top, rc.right, rc.top + t},
                {rc.left, rc.bottom - t, rc.right, rc.bottom},
                {rc.left, rc.top, rc.left + t, rc.bottom},
                {rc.right - t, rc.top, rc.right, rc.bottom},
            };
            HBRUSH outline = CreateSolidBrush(g_settings.outlineColor);
            for (const RECT& edge : edges) FillRect(dc, &edge, outline);
            DeleteObject(outline);

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_TIMER: {
            g_flashTick++;
            if (g_flashTick > kFlashHoldTicks + kFlashFadeTicks) {
                DestroyWindow(hwnd);
            } else if (g_flashTick > kFlashHoldTicks) {
                const int a = g_settings.outlineAlpha;
                const int faded =
                    a - a * (g_flashTick - kFlashHoldTicks) / kFlashFadeTicks;
                SetLayeredWindowAttributes(hwnd, kFlashTransparentColor,
                                           (BYTE)faded,
                                           LWA_COLORKEY | LWA_ALPHA);
            }
            return 0;
        }
        case WM_DESTROY:
            if (g_flashWindow == hwnd) g_flashWindow = nullptr;
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

static void FlashMonitorOutline(const MonitorInfo& mon) {
    if (g_flashWindow) DestroyWindow(g_flashWindow);

    const RECT& rc = mon.rcMon;
    HWND hwnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT |
                                   WS_EX_TOPMOST | WS_EX_TOOLWINDOW |
                                   WS_EX_NOACTIVATE,
                               kFlashClass, nullptr, WS_POPUP, rc.left, rc.top,
                               rc.right - rc.left, rc.bottom - rc.top, nullptr,
                               nullptr, GetModuleHandle(nullptr), nullptr);
    if (!hwnd) return;

    g_flashWindow = hwnd;
    g_flashTick = 0;
    g_flashThickness = MulDiv(g_settings.outlineWidth, mon.dpi, 96);
    SetLayeredWindowAttributes(hwnd, kFlashTransparentColor,
                               g_settings.outlineAlpha,
                               LWA_COLORKEY | LWA_ALPHA);
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    UpdateWindow(hwnd);
    SetTimer(hwnd, kFlashTimerId, 16, nullptr);
}

// direction: +1 next monitor, -1 previous (left to right, wrapping around).
static void FocusMonitor(int direction) {
    const int n = (int)g_monitors.size();
    const int cur = FindMonitorIndex(GetSourceMonitor());
    if (n < 2 || cur < 0) return;

    // Skip monitors without windows.
    for (int step = 1; step < n; step++) {
        const int idx = ((cur + direction * step) % n + n) % n;
        const auto windows = GetWindowsOnMonitor(g_monitors[idx].hMon);
        if (windows.empty()) continue;

        Wh_Log(L"Focusing monitor %d", idx);
        ActivateWindow(windows.front());
        if (g_settings.outlineEnabled) FlashMonitorOutline(g_monitors[idx]);
        return;
    }
}

// ── keyboard hook ─────────────────────────────────────────────────────────────

static const UINT WM_APP_ACTION = WM_APP + 1;  // wParam: Action
static const UINT WM_APP_RELOAD_SETTINGS = WM_APP + 2;

static std::atomic<HWND> g_mainWindow;
static HHOOK g_keyboardHook;

// The key of a shortcut that fired. Its auto-repeats and key-up are blocked
// too, unless a later key-down of it was passed on.
static DWORD g_blockedKey;

// Double tap state.
static const DWORD kTapMaxHoldMs = 250;  // longest press that counts as a tap
static const DWORD kDoubleTapMs = 400;   // longest gap between the two taps
static bool g_tapKeyDown;
static bool g_tapInterrupted;  // another key was pressed during the tap
static DWORD g_tapPressTime;
static DWORD g_lastTapTime;

static bool KeyDown(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

static bool SideMatches(BYTE need, bool left, bool right) {
    switch (need) {
        case kNone:
            return !left && !right;
        case kLeft:
            return left && !right;
        case kRight:
            return right && !left;
        case kEither:
            return left || right;
        default:
            return left && right;
    }
}

// The shortcut's modifiers are held, and no others.
static bool ModifiersMatch(const Shortcut& s) {
    if (KeyDown(VK_LWIN) || KeyDown(VK_RWIN)) return false;

    bool lctrl = KeyDown(VK_LCONTROL);
    const bool ralt = KeyDown(VK_RMENU);
    // AltGr keyboard layouts press a fake Left Ctrl along with Right Alt.
    if (ralt && s.ctrl == kNone && s.alt != kNone && s.alt != kLeft) {
        lctrl = false;
    }

    return SideMatches(s.ctrl, lctrl, KeyDown(VK_RCONTROL)) &&
           SideMatches(s.shift, KeyDown(VK_LSHIFT), KeyDown(VK_RSHIFT)) &&
           SideMatches(s.alt, KeyDown(VK_LMENU), ralt);
}

static int FindMatchingShortcut(DWORD vk) {
    for (int i = 0; i < kActionCount; i++) {
        const Shortcut& s = g_settings.shortcuts[i];
        // A shortcut without modifiers would block normal typing.
        if (s.vk != vk) continue;
        if (s.ctrl == kNone && s.shift == kNone && s.alt == kNone) continue;
        if (ModifiersMatch(s)) return i;
    }
    return -1;
}

// Whether the action would do something right now. If not, the key press is
// passed on to the app (for example Ctrl + Left word navigation when there's
// no monitor on the left).
static bool ActionHasTarget(int action) {
    switch (action) {
        case kMoveWindowLeft:
        case kMoveWindowRight: {
            HWND hwnd = GetActiveTopLevelWindow();
            if (!hwnd) return false;
            const int cur = FindMonitorIndex(
                MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST));
            return FindNeighbor(cur, action == kMoveWindowLeft ? -1 : 1) >= 0;
        }
        case kMoveAllLeft:
        case kMoveAllRight:
            return FindNeighbor(FindMonitorIndex(GetSourceMonitor()),
                                action == kMoveAllLeft ? -1 : 1) >= 0;
        case kMinimizeTop:
            return GetActiveTopLevelWindow() != nullptr;
        case kRestoreMinimized:
            return HasRestorableWindow();
        case kFocusNext:
        case kFocusPrevious:
            return g_monitors.size() >= 2;
    }
    return false;
}

// When a blocked key was pressed with Alt held, the app would see Alt pressed
// and released alone and open its menu bar. An unassigned key in between
// prevents that.
static void SendMenuMaskKey() {
    INPUT in[2] = {};
    in[0].type = in[1].type = INPUT_KEYBOARD;
    in[0].ki.wVk = in[1].ki.wVk = 0xE8;
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, in, sizeof(INPUT));
}

static void TrackDoubleTap(DWORD vk, bool down, bool up) {
    const UINT tapVk = g_settings.doubleTapVk;
    if (!tapVk) return;

    if (vk != tapVk) {
        if (down) {
            // Any other key cancels a tap in progress or a pending first tap.
            if (g_tapKeyDown) g_tapInterrupted = true;
            g_lastTapTime = 0;
        }
        return;
    }

    if (down) {
        if (!g_tapKeyDown) {  // ignore auto-repeat
            g_tapKeyDown = true;
            g_tapInterrupted = false;
            g_tapPressTime = GetTickCount();
        }
        return;
    }
    if (!up) return;

    g_tapKeyDown = false;
    const DWORD now = GetTickCount();
    if (g_tapInterrupted || now - g_tapPressTime > kTapMaxHoldMs) {
        g_lastTapTime = 0;
    } else if (g_lastTapTime && now - g_lastTapTime <= kDoubleTapMs) {
        g_lastTapTime = 0;
        if (g_monitors.size() >= 2) {
            PostMessage(g_mainWindow, WM_APP_ACTION, kFocusNext, 0);
        }
    } else {
        g_lastTapTime = now;
    }
}

static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode != HC_ACTION) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    const auto* kb = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
    // Ignore synthetic input, including the mod's own.
    if (kb->flags & LLKHF_INJECTED) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    const DWORD vk = kb->vkCode;
    const bool down = wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;
    const bool up = wParam == WM_KEYUP || wParam == WM_SYSKEYUP;
    TrackDoubleTap(vk, down, up);

    if (up) {
        if (vk == g_blockedKey) {
            g_blockedKey = 0;
            return 1;
        }
    } else if (down) {
        const int action = FindMatchingShortcut(vk);
        if (action >= 0 && vk == g_blockedKey) {
            return 1;  // auto-repeat of a shortcut that already fired
        }
        if (action >= 0 && ActionHasTarget(action)) {
            g_blockedKey = vk;
            PostMessage(g_mainWindow, WM_APP_ACTION, action, 0);
            if (KeyDown(VK_MENU)) SendMenuMaskKey();
            return 1;
        }
        // This key-down is passed on (for example the modifier was released
        // while the key auto-repeats), so its key-up must be passed on too.
        if (vk == g_blockedKey) g_blockedKey = 0;
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

// ── worker thread ─────────────────────────────────────────────────────────────

static const wchar_t kMainClass[] = L"WH_MultiMonitorWindowControls";

static void RunAction(HWND hwnd, int action) {
    RefreshMonitors();
    switch (action) {
        case kMoveWindowLeft:
            MoveActiveWindow(-1);
            break;
        case kMoveWindowRight:
            MoveActiveWindow(1);
            break;
        case kMoveAllLeft:
            MoveAllWindows(hwnd, -1);
            break;
        case kMoveAllRight:
            MoveAllWindows(hwnd, 1);
            break;
        case kMinimizeTop:
            MinimizeTopWindow();
            break;
        case kRestoreMinimized:
            RestoreMinimizedWindow();
            break;
        case kFocusNext:
            FocusMonitor(1);
            break;
        case kFocusPrevious:
            FocusMonitor(-1);
            break;
    }
}

// A hidden top-level window (not message-only, so it also receives display
// change broadcasts).
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam) {
    switch (msg) {
        case WM_APP_ACTION:
            RunAction(hwnd, (int)wParam);
            return 0;
        case WM_APP_RELOAD_SETTINGS:
            LoadSettings();
            return 0;
        case WM_DISPLAYCHANGE:
            RefreshMonitors();
            return 0;
        case WM_SETTINGCHANGE:
            if (wParam == SPI_SETWORKAREA) RefreshMonitors();
            return 0;
        case WM_TIMER:
            if (wParam == kRefocusTimerId) {
                KillTimer(hwnd, kRefocusTimerId);
                if (IsWindow(g_refocusWindow)) ActivateWindow(g_refocusWindow);
                g_refocusWindow = nullptr;
            }
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

static HANDLE g_thread;
static DWORD g_threadId;

static DWORD WINAPI WorkerThread(LPVOID) {
    LoadSettings();
    RefreshMonitors();

    const HINSTANCE instance = GetModuleHandle(nullptr);
    WNDCLASSEX wc = {sizeof(wc)};
    wc.hInstance = instance;
    wc.lpfnWndProc = MainWndProc;
    wc.lpszClassName = kMainClass;
    RegisterClassEx(&wc);
    wc.lpfnWndProc = FlashWndProc;
    wc.lpszClassName = kFlashClass;
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, kMainClass, nullptr, WS_POPUP,
                               0, 0, 0, 0, nullptr, nullptr, instance, nullptr);
    if (hwnd) {
        g_mainWindow = hwnd;
        g_keyboardHook =
            SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, instance, 0);
        if (!g_keyboardHook) {
            Wh_Log(L"SetWindowsHookEx failed: %u", GetLastError());
        }

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0) > 0) {
            DispatchMessage(&msg);
        }

        if (g_keyboardHook) UnhookWindowsHookEx(g_keyboardHook);
        if (g_flashWindow) DestroyWindow(g_flashWindow);
        g_mainWindow = nullptr;
        DestroyWindow(hwnd);
    } else {
        Wh_Log(L"CreateWindowEx failed: %u", GetLastError());
    }

    UnregisterClass(kMainClass, instance);
    UnregisterClass(kFlashClass, instance);
    return 0;
}

BOOL WhTool_ModInit() {
    g_thread = CreateThread(nullptr, 0, WorkerThread, nullptr, 0, &g_threadId);
    return g_thread != nullptr;
}

void WhTool_ModSettingsChanged() {
    // Settings are read on the worker thread, where the hook uses them.
    if (HWND hwnd = g_mainWindow) PostMessage(hwnd, WM_APP_RELOAD_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    PostThreadMessage(g_threadId, WM_QUIT, 0, 0);
    WaitForSingleObject(g_thread, 3000);
    CloseHandle(g_thread);
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
