#pragma once

namespace Tmpl8 {

    enum class KeyCode : uint8_t {
        Unknown = 0x00,

        Backspace = 0x08,
        Tab = 0x09,
        Enter = 0x0D,
        Shift = 0x10,
        Control = 0x11,
        Alt = 0x12,
        Pause = 0x13,
        CapsLock = 0x14,
        Escape = 0x1B,
        Space = 0x20,
        PrintScreen = 0x2C,

        PageUp = 0x21,
        PageDown = 0x22,
        End = 0x23,
        Home = 0x24,
        Left = 0x25,
        Up = 0x26,
        Right = 0x27,
        Down = 0x28,
        Insert = 0x2D,
        Delete = 0x2E,

        D0 = 0x30,
        D1 = 0x31,
        D2 = 0x32,
        D3 = 0x33,
        D4 = 0x34,
        D5 = 0x35,
        D6 = 0x36,
        D7 = 0x37,
        D8 = 0x38,
        D9 = 0x39,

        A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        LWin = 0x5B,
        RWin = 0x5C,

        Num0 = 0x60,
        Num1 = 0x61,
        Num2 = 0x62,
        Num3 = 0x63,
        Num4 = 0x64,
        Num5 = 0x65,
        Num6 = 0x66,
        Num7 = 0x67,
        Num8 = 0x68,
        Num9 = 0x69,
        Multiply = 0x6A,
        Add = 0x6B,
        Separator = 0x6C,
        Subtract = 0x6D,
        Decimal = 0x6E,
        Divide = 0x6F,

        F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        NumLock = 0x90,
        ScrollLock = 0x91,

        LShift = 0xA0,
        RShift = 0xA1,
        LControl = 0xA2,
        RControl = 0xA3,
        LAlt = 0xA4,
        RAlt = 0xA5,

        VolumeMute = 0xAD,
        VolumeDown = 0xAE,
        VolumeUp = 0xAF,
        NextTrack = 0xB0,
        PrevTrack = 0xB1,
        PlayPause = 0xB3,

        Semicolon = 0xBA, // ;:
        Plus = 0xBB,      // =+
        Comma = 0xBC,     // ,<
        Minus = 0xBD,     // -_
        Period = 0xBE,    // .>
        Slash = 0xBF,     // /?
        Tilde = 0xC0,     // `~
        LBracket = 0xDB,  // [{
        Backslash = 0xDC, // \|
        RBracket = 0xDD,  // ]}
        Quote = 0xDE      // '"
    };

	class Input{
	public:
		static uint* keystates;
		static bool IsKeyDown(uint keycode);
		static bool IsKeyDown(KeyCode keycode);
	};
}