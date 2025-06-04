#include "convertOGL.h"
#include <glm/glm.hpp>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>

namespace Neon
{
    GLenum ConvertOGL::typeinfoToGL(const std::type_info *type)
    {
        if (!type) return GL_INVALID_ENUM;

        static const std::unordered_map<size_t, GLenum> typeMap =
        {
            // --- Floating point types ---
            {typeid(float).hash_code(), GL_FLOAT},
            {typeid(double).hash_code(), GL_DOUBLE},

            // --- Signed integer types ---
            {typeid(int8_t).hash_code(), GL_BYTE},
            {typeid(signed char).hash_code(), GL_BYTE},
            {typeid(int16_t).hash_code(), GL_SHORT},
            {typeid(short).hash_code(), GL_SHORT},
            {typeid(int32_t).hash_code(), GL_INT},
            {typeid(int).hash_code(), GL_INT},

            // --- Unsigned integer types ---
            {typeid(uint8_t).hash_code(), GL_UNSIGNED_BYTE},
            {typeid(unsigned char).hash_code(), GL_UNSIGNED_BYTE},
            {typeid(uint16_t).hash_code(), GL_UNSIGNED_SHORT},
            {typeid(unsigned short).hash_code(), GL_UNSIGNED_SHORT},
            {typeid(uint32_t).hash_code(), GL_UNSIGNED_INT},
            {typeid(unsigned int).hash_code(), GL_UNSIGNED_INT},

            // --- GLM Types ---
            // GLM vector types (vec2, vec3, vec4) are composed of floats.
            // Their OpenGL type is GL_FLOAT.
            {typeid(glm::vec2).hash_code(), GL_FLOAT},
            {typeid(glm::vec3).hash_code(), GL_FLOAT},
            {typeid(glm::vec4).hash_code(), GL_FLOAT},

            // GLM integer vector types (ivec2, ivec3, ivec4) are composed of ints.
            // Their OpenGL type is GL_INT.
            {typeid(glm::ivec2).hash_code(), GL_INT},
            {typeid(glm::ivec3).hash_code(), GL_INT},
            {typeid(glm::ivec4).hash_code(), GL_INT},

            // GLM unsigned integer vector types (uvec2, uvec3, uvec4) are composed of unsigned ints.
            // Their OpenGL type is GL_UNSIGNED_INT.
            {typeid(glm::uvec2).hash_code(), GL_UNSIGNED_INT},
            {typeid(glm::uvec3).hash_code(), GL_UNSIGNED_INT},
            {typeid(glm::uvec4).hash_code(), GL_UNSIGNED_INT},

            // GLM matrix types (mat2, mat3, mat4) are composed of floats.
            // Their OpenGL type is GL_FLOAT, as each column is a vector of floats.
            {typeid(glm::mat2).hash_code(), GL_FLOAT},
            {typeid(glm::mat3).hash_code(), GL_FLOAT},
            {typeid(glm::mat4).hash_code(), GL_FLOAT},
        };

        const auto it = typeMap.find(type->hash_code());
        if (it != typeMap.end()) return it->second;

        return GL_INVALID_ENUM;
    }

    GLenum ConvertOGL::shaderTypeToGL(const ShaderType type)
    {
        if(type == ShaderType::Vertex) return GL_VERTEX_SHADER;
        if(type == ShaderType::Fragment) return GL_FRAGMENT_SHADER;
        if(type == ShaderType::Compute) return GL_COMPUTE_SHADER;
        return GL_INVALID_ENUM;
    }

    uint32_t ConvertOGL::getComponentCount(const std::type_info* type)
    {
        if (!type) return 1; // Handle null pointer

        // Basic Numeric Types
        if (*type == typeid(float) || *type == typeid(int) || *type == typeid(unsigned int) ||
            *type == typeid(uint32_t) || *type == typeid(double) || *type == typeid(bool)) return 1;

        // GLM Vector Types
        if (*type == typeid(glm::vec2) || *type == typeid(glm::ivec2) || *type == typeid(glm::uvec2)) return 2;
        if (*type == typeid(glm::vec3) || *type == typeid(glm::ivec3) || *type == typeid(glm::uvec3)) return 3;
        if (*type == typeid(glm::vec4) || *type == typeid(glm::ivec4) || *type == typeid(glm::uvec4)) return 4;

        // GLM Matrix Types (components per column)
        if (*type == typeid(glm::mat2)) return 2;
        if (*type == typeid(glm::mat3)) return 3;
        if (*type == typeid(glm::mat4)) return 4;

        // Fallback for unknown types
        return 1;
    }

    KeyCode ConvertOGL::keyCodeFromSDL(SDL_Keycode sdlKey)
{
    switch (sdlKey) {
        case SDLK_RETURN:      return KeyCode::Return;
        case SDLK_ESCAPE:      return KeyCode::Escape;
        case SDLK_BACKSPACE:   return KeyCode::Backspace;
        case SDLK_TAB:         return KeyCode::Tab;
        case SDLK_SPACE:       return KeyCode::Space;
        case SDLK_EXCLAIM:     return KeyCode::Exclaim;
        case SDLK_DBLAPOSTROPHE:    return KeyCode::DblApostrophe;
        case SDLK_HASH:        return KeyCode::Hash;
        case SDLK_DOLLAR:      return KeyCode::Dollar;
        case SDLK_PERCENT:     return KeyCode::Percent;
        case SDLK_AMPERSAND:   return KeyCode::Ampersand;
        case SDLK_APOSTROPHE:       return KeyCode::Apostrophe;
        case SDLK_LEFTPAREN:   return KeyCode::LeftParen;
        case SDLK_RIGHTPAREN:  return KeyCode::RightParen;
        case SDLK_ASTERISK:    return KeyCode::Asterisk;
        case SDLK_PLUS:        return KeyCode::Plus;
        case SDLK_COMMA:       return KeyCode::Comma;
        case SDLK_MINUS:       return KeyCode::Minus;
        case SDLK_PERIOD:      return KeyCode::Period;
        case SDLK_SLASH:       return KeyCode::Slash;
        case SDLK_0:           return KeyCode::Num0;
        case SDLK_1:           return KeyCode::Num1;
        case SDLK_2:           return KeyCode::Num2;
        case SDLK_3:           return KeyCode::Num3;
        case SDLK_4:           return KeyCode::Num4;
        case SDLK_5:           return KeyCode::Num5;
        case SDLK_6:           return KeyCode::Num6;
        case SDLK_7:           return KeyCode::Num7;
        case SDLK_8:           return KeyCode::Num8;
        case SDLK_9:           return KeyCode::Num9;
        case SDLK_COLON:       return KeyCode::Colon;
        case SDLK_SEMICOLON:   return KeyCode::Semicolon;
        case SDLK_LESS:        return KeyCode::Less;
        case SDLK_EQUALS:      return KeyCode::Equals;
        case SDLK_GREATER:     return KeyCode::Greater;
        case SDLK_QUESTION:    return KeyCode::Question;
        case SDLK_AT:          return KeyCode::At;
        case SDLK_LEFTBRACKET: return KeyCode::LeftBracket;
        case SDLK_BACKSLASH:   return KeyCode::Backslash;
        case SDLK_RIGHTBRACKET:return KeyCode::RightBracket;
        case SDLK_CARET:       return KeyCode::Caret;
        case SDLK_UNDERSCORE:  return KeyCode::Underscore;
        case SDLK_GRAVE:   return KeyCode::Grave;
        case SDLK_A:           return KeyCode::A;
        case SDLK_B:           return KeyCode::B;
        case SDLK_C:           return KeyCode::C;
        case SDLK_D:           return KeyCode::D;
        case SDLK_E:           return KeyCode::E;
        case SDLK_F:           return KeyCode::F;
        case SDLK_G:           return KeyCode::G;
        case SDLK_H:           return KeyCode::H;
        case SDLK_I:           return KeyCode::I;
        case SDLK_J:           return KeyCode::J;
        case SDLK_K:           return KeyCode::K;
        case SDLK_L:           return KeyCode::L;
        case SDLK_M:           return KeyCode::M;
        case SDLK_N:           return KeyCode::N;
        case SDLK_O:           return KeyCode::O;
        case SDLK_P:           return KeyCode::P;
        case SDLK_Q:           return KeyCode::Q;
        case SDLK_R:           return KeyCode::R;
        case SDLK_S:           return KeyCode::S;
        case SDLK_T:           return KeyCode::T;
        case SDLK_U:           return KeyCode::U;
        case SDLK_V:           return KeyCode::V;
        case SDLK_W:           return KeyCode::W;
        case SDLK_X:           return KeyCode::X;
        case SDLK_Y:           return KeyCode::Y;
        case SDLK_Z:           return KeyCode::Z;
        case SDLK_LEFTBRACE:   return KeyCode::LeftBrace;
        case SDLK_PIPE:         return KeyCode::Pipe;
        case SDLK_RIGHTBRACE:  return KeyCode::RightBrace;
        case SDLK_TILDE:       return KeyCode::Tilde;
        case SDLK_DELETE:      return KeyCode::Delete;

        // Function keys
        case SDLK_CAPSLOCK:    return KeyCode::CapsLock;
        case SDLK_F1:          return KeyCode::F1;
        case SDLK_F2:          return KeyCode::F2;
        case SDLK_F3:          return KeyCode::F3;
        case SDLK_F4:          return KeyCode::F4;
        case SDLK_F5:          return KeyCode::F5;
        case SDLK_F6:          return KeyCode::F6;
        case SDLK_F7:          return KeyCode::F7;
        case SDLK_F8:          return KeyCode::F8;
        case SDLK_F9:          return KeyCode::F9;
        case SDLK_F10:         return KeyCode::F10;
        case SDLK_F11:         return KeyCode::F11;
        case SDLK_F12:         return KeyCode::F12;

        case SDLK_PRINTSCREEN: return KeyCode::PrintScreen;
        case SDLK_SCROLLLOCK:  return KeyCode::ScrollLock;
        case SDLK_PAUSE:       return KeyCode::Pause;
        case SDLK_INSERT:      return KeyCode::Insert;
        case SDLK_HOME:        return KeyCode::Home;
        case SDLK_PAGEUP:      return KeyCode::PageUp;
        case SDLK_END:         return KeyCode::End;
        case SDLK_PAGEDOWN:    return KeyCode::PageDown;
        case SDLK_RIGHT:       return KeyCode::Right;
        case SDLK_LEFT:        return KeyCode::Left;
        case SDLK_DOWN:        return KeyCode::Down;
        case SDLK_UP:          return KeyCode::Up;
        case SDLK_NUMLOCKCLEAR:return KeyCode::NumLockClear;
        case SDLK_KP_DIVIDE:   return KeyCode::KpDivide;
        case SDLK_KP_MULTIPLY: return KeyCode::KpMultiply;
        case SDLK_KP_MINUS:    return KeyCode::KpMinus;
        case SDLK_KP_PLUS:     return KeyCode::KpPlus;
        case SDLK_KP_ENTER:    return KeyCode::KpEnter;
        case SDLK_KP_1:        return KeyCode::Kp1;
        case SDLK_KP_2:        return KeyCode::Kp2;
        case SDLK_KP_3:        return KeyCode::Kp3;
        case SDLK_KP_4:        return KeyCode::Kp4;
        case SDLK_KP_5:        return KeyCode::Kp5;
        case SDLK_KP_6:        return KeyCode::Kp6;
        case SDLK_KP_7:        return KeyCode::Kp7;
        case SDLK_KP_8:        return KeyCode::Kp8;
        case SDLK_KP_9:        return KeyCode::Kp9;
        case SDLK_KP_0:        return KeyCode::Kp0;
        case SDLK_KP_PERIOD:   return KeyCode::KpPeriod;
        case SDLK_APPLICATION: return KeyCode::Application;
        case SDLK_POWER:       return KeyCode::Power;
        case SDLK_KP_EQUALS:   return KeyCode::KpEquals;
        case SDLK_F13:         return KeyCode::F13;
        case SDLK_F14:         return KeyCode::F14;
        case SDLK_F15:         return KeyCode::F15;
        case SDLK_F16:         return KeyCode::F16;
        case SDLK_F17:         return KeyCode::F17;
        case SDLK_F18:         return KeyCode::F18;
        case SDLK_F19:         return KeyCode::F19;
        case SDLK_F20:         return KeyCode::F20;
        case SDLK_F21:         return KeyCode::F21;
        case SDLK_F22:         return KeyCode::F22;
        case SDLK_F23:         return KeyCode::F23;
        case SDLK_F24:         return KeyCode::F24;

        // Numpad “extras” and miscellaneous
        case SDLK_EXECUTE:     return KeyCode::Execute;
        case SDLK_HELP:        return KeyCode::Help;
        case SDLK_MENU:        return KeyCode::Menu;
        case SDLK_SELECT:      return KeyCode::Select;
        case SDLK_STOP:        return KeyCode::Stop;
        case SDLK_AGAIN:       return KeyCode::Again;
        case SDLK_UNDO:        return KeyCode::Undo;
        case SDLK_CUT:         return KeyCode::Cut;
        case SDLK_COPY:        return KeyCode::Copy;
        case SDLK_PASTE:       return KeyCode::Paste;
        case SDLK_FIND:        return KeyCode::Find;
        case SDLK_MUTE:        return KeyCode::Mute;
        case SDLK_VOLUMEUP:    return KeyCode::VolumeUp;
        case SDLK_VOLUMEDOWN:  return KeyCode::VolumeDown;
        case SDLK_KP_COMMA:    return KeyCode::KpComma;
        case SDLK_KP_EQUALSAS400: return KeyCode::KpEqualsAs400;
        case SDLK_ALTERASE:    return KeyCode::AltErase;
        case SDLK_SYSREQ:      return KeyCode::SysReq;
        case SDLK_CANCEL:      return KeyCode::Cancel;
        case SDLK_CLEAR:       return KeyCode::Clear;
        case SDLK_PRIOR:       return KeyCode::Prior;
        case SDLK_RETURN2:     return KeyCode::Return2;
        case SDLK_SEPARATOR:   return KeyCode::Separator;
        case SDLK_OUT:         return KeyCode::Out;
        case SDLK_OPER:        return KeyCode::Oper;
        case SDLK_CLEARAGAIN:  return KeyCode::ClearAgain;
        case SDLK_CRSEL:       return KeyCode::CrSel;
        case SDLK_EXSEL:       return KeyCode::ExSel;
        case SDLK_KP_00:       return KeyCode::Kp00;
        case SDLK_KP_000:      return KeyCode::Kp000;
        case SDLK_THOUSANDSSEPARATOR: return KeyCode::ThousandsSeparator;
        case SDLK_DECIMALSEPARATOR:   return KeyCode::DecimalSeparator;
        case SDLK_CURRENCYUNIT:       return KeyCode::CurrencyUnit;
        case SDLK_CURRENCYSUBUNIT:    return KeyCode::CurrencySubUnit;
        case SDLK_KP_LEFTPAREN:       return KeyCode::KpLeftParen;
        case SDLK_KP_RIGHTPAREN:      return KeyCode::KpRightParen;
        case SDLK_KP_LEFTBRACE:       return KeyCode::KpLeftBrace;
        case SDLK_KP_RIGHTBRACE:      return KeyCode::KpRightBrace;
        case SDLK_KP_TAB:             return KeyCode::KpTab;
        case SDLK_KP_BACKSPACE:       return KeyCode::KpBackspace;
        case SDLK_KP_A:               return KeyCode::KpA;
        case SDLK_KP_B:               return KeyCode::KpB;
        case SDLK_KP_C:               return KeyCode::KpC;
        case SDLK_KP_D:               return KeyCode::KpD;
        case SDLK_KP_E:               return KeyCode::KpE;
        case SDLK_KP_F:               return KeyCode::KpF;
        case SDLK_KP_XOR:             return KeyCode::KpXor;
        case SDLK_KP_POWER:           return KeyCode::KpPower;
        case SDLK_KP_PERCENT:         return KeyCode::KpPercent;
        case SDLK_KP_LESS:            return KeyCode::KpLess;
        case SDLK_KP_GREATER:         return KeyCode::KpGreater;
        case SDLK_KP_AMPERSAND:       return KeyCode::KpAmpersand;
        case SDLK_KP_DBLAMPERSAND:    return KeyCode::KpDblAmpersand;
        case SDLK_KP_VERTICALBAR:     return KeyCode::KpVerticalBar;
        case SDLK_KP_DBLVERTICALBAR:  return KeyCode::KpDblVerticalBar;
        case SDLK_KP_COLON:           return KeyCode::KpColon;
        case SDLK_KP_HASH:            return KeyCode::KpHash;
        case SDLK_KP_SPACE:           return KeyCode::KpSpace;
        case SDLK_KP_AT:              return KeyCode::KpAt;
        case SDLK_KP_EXCLAM:          return KeyCode::KpExclam;
        case SDLK_KP_MEMSTORE:        return KeyCode::KpMemStore;
        case SDLK_KP_MEMRECALL:       return KeyCode::KpMemRecall;
        case SDLK_KP_MEMCLEAR:        return KeyCode::KpMemClear;
        case SDLK_KP_MEMADD:          return KeyCode::KpMemAdd;
        case SDLK_KP_MEMSUBTRACT:     return KeyCode::KpMemSubtract;
        case SDLK_KP_MEMMULTIPLY:     return KeyCode::KpMemMultiply;
        case SDLK_KP_MEMDIVIDE:       return KeyCode::KpMemDivide;
        case SDLK_KP_PLUSMINUS:       return KeyCode::KpPlusMinus;
        case SDLK_KP_CLEAR:           return KeyCode::KpClear;
        case SDLK_KP_CLEARENTRY:      return KeyCode::KpClearEntry;
        case SDLK_KP_BINARY:          return KeyCode::KpBinary;
        case SDLK_KP_OCTAL:           return KeyCode::KpOctal;
        case SDLK_KP_DECIMAL:         return KeyCode::KpDecimal;
        case SDLK_KP_HEXADECIMAL:     return KeyCode::KpHexadecimal;

        // Modifier keys
        case SDLK_LCTRL:       return KeyCode::LCtrl;
        case SDLK_LSHIFT:      return KeyCode::LShift;
        case SDLK_LALT:        return KeyCode::LAlt;
        case SDLK_LGUI:        return KeyCode::LGui;
        case SDLK_RCTRL:       return KeyCode::RCtrl;
        case SDLK_RSHIFT:      return KeyCode::RShift;
        case SDLK_RALT:        return KeyCode::RAlt;
        case SDLK_RGUI:        return KeyCode::RGui;

        // Some OEM / special keys
        case SDLK_MODE:        return KeyCode::Mode;
        case SDLK_SLEEP:       return KeyCode::Sleep;
        case SDLK_MEDIA_NEXT_TRACK:   return KeyCode::MediaNextTrack;
        case SDLK_MEDIA_PREVIOUS_TRACK:   return KeyCode::MediaPreviousTrack;
        case SDLK_MEDIA_STOP:   return KeyCode::MediaStop;
        case SDLK_MEDIA_PLAY:   return KeyCode::MediaPlay;

        default:
            return KeyCode::Unknown;
    }
}

    KeyMod ConvertOGL::keyModFromSDL(const SDL_Keymod sdlMod)
    {
        auto mod = KeyMod::None;
        if (sdlMod & SDL_KMOD_LSHIFT)  mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::LShift));
        if (sdlMod & SDL_KMOD_RSHIFT)  mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::RShift));
        if (sdlMod & SDL_KMOD_LCTRL)   mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::LCtrl));
        if (sdlMod & SDL_KMOD_RCTRL)   mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::RCtrl));
        if (sdlMod & SDL_KMOD_LALT)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::LAlt));
        if (sdlMod & SDL_KMOD_RALT)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::RAlt));
        if (sdlMod & SDL_KMOD_LGUI)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::LGui));
        if (sdlMod & SDL_KMOD_RGUI)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::RGui));
        if (sdlMod & SDL_KMOD_NUM)     mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::Num));
        if (sdlMod & SDL_KMOD_CAPS)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::Caps));
        if (sdlMod & SDL_KMOD_MODE)    mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::Mode));
        if (sdlMod & SDL_KMOD_SCROLL)  mod = static_cast<KeyMod>(static_cast<uint16_t>(mod) | static_cast<uint16_t>(KeyMod::Scroll));
        return mod;
    }

    MouseButton ConvertOGL::mouseButtonFromSDL(const uint8_t sdlBtn)
    {
        switch (sdlBtn)
        {
            case SDL_BUTTON_LEFT:   return MouseButton::Left;
            case SDL_BUTTON_MIDDLE: return MouseButton::Middle;
            case SDL_BUTTON_RIGHT:  return MouseButton::Right;
            case SDL_BUTTON_X1:     return MouseButton::Side1;
            case SDL_BUTTON_X2:     return MouseButton::Side2;
            default:                return MouseButton::None;
        }
    }

}
