//
// Created by Shreejit Murthy on 29/9/2024.
//

#pragma once
#include <SDL3/SDL.h>
#include <vector>

#define MAX_KEYS 322

// From SDL_keycode.h, simply shortened
constexpr uint32_t KRET     =  0x0000000du;
constexpr uint32_t KESC     =  0x0000001bu;
constexpr uint32_t KBCKSPCE =  0x00000008u;
constexpr uint32_t KTAB     =  0x00000009u;
constexpr uint32_t KSPCE    =  0x00000020u;
constexpr uint32_t K0       =  0x00000030u;
constexpr uint32_t K1       =  0x00000031u;
constexpr uint32_t K2       =  0x00000032u;
constexpr uint32_t K3       =  0x00000033u;
constexpr uint32_t K4       =  0x00000034u;
constexpr uint32_t K5       =  0x00000035u;
constexpr uint32_t K6       =  0x00000036u;
constexpr uint32_t K7       =  0x00000037u;
constexpr uint32_t K8       =  0x00000038u;
constexpr uint32_t K9       =  0x00000039u;
constexpr uint32_t KA       =  0x00000061u;
constexpr uint32_t KB       =  0x00000062u;
constexpr uint32_t KC       =  0x00000063u;
constexpr uint32_t KD       =  0x00000064u;
constexpr uint32_t KE       =  0x00000065u;
constexpr uint32_t KF       =  0x00000066u;
constexpr uint32_t KG       =  0x00000067u;
constexpr uint32_t KH       =  0x00000068u;
constexpr uint32_t KI       =  0x00000069u;
constexpr uint32_t KJ       =  0x0000006au;
constexpr uint32_t KK       =  0x0000006bu;
constexpr uint32_t KL       =  0x0000006cu;
constexpr uint32_t KM       =  0x0000006du;
constexpr uint32_t KN       =  0x0000006eu;
constexpr uint32_t KO       =  0x0000006fu;
constexpr uint32_t KP       =  0x00000070u;
constexpr uint32_t KQ       =  0x00000071u;
constexpr uint32_t KR       =  0x00000072u;
constexpr uint32_t KS       =  0x00000073u;
constexpr uint32_t KT       =  0x00000074u;
constexpr uint32_t KU       =  0x00000075u;
constexpr uint32_t KV       =  0x00000076u;
constexpr uint32_t KW       =  0x00000077u;
constexpr uint32_t KX       =  0x00000078u;
constexpr uint32_t KY       =  0x00000079u;
constexpr uint32_t KZ       =  0x0000007au;
constexpr uint32_t KDEL     =  0x0000007fu;
constexpr uint32_t KF1      =  0x4000003au;
constexpr uint32_t KF2      =  0x4000003bu;
constexpr uint32_t KF3      =  0x4000003cu;
constexpr uint32_t KF4      =  0x4000003du;
constexpr uint32_t KF5      =  0x4000003eu;
constexpr uint32_t KF6      =  0x4000003fu;
constexpr uint32_t KF7      =  0x40000040u;
constexpr uint32_t KF8      =  0x40000041u;
constexpr uint32_t KF9      =  0x40000042u;
constexpr uint32_t KF10     =  0x40000043u;
constexpr uint32_t KF11     =  0x40000044u;
constexpr uint32_t KF12     =  0x40000045u;
constexpr uint32_t KRIGHT   =  0x4000004fu;
constexpr uint32_t KLEFT    =  0x40000050u;
constexpr uint32_t KDOWN    =  0x40000051u;
constexpr uint32_t KUP      =  0x40000052u;
constexpr uint32_t KLCTRL   =  0x400000e0u;
constexpr uint32_t KLSHIFT  =  0x400000e1u;
constexpr uint32_t KLALT    =  0x400000e2u;
constexpr uint32_t KRCTRL   =  0x400000e4u;
constexpr uint32_t KRSHIFT  =  0x400000e5u;
constexpr uint32_t KRALT    =  0x400000e6u;

class Keyboard {
public:
    Keyboard();
    void process(SDL_Event event);
    bool isDown(uint32_t key);
    bool isPressed(uint32_t key);  // Check for key press (single event)
    bool isReleased(uint32_t key); // Check for key release (single event)
    void reset();                  // Reset pressed and released states after processing
private:
    std::vector<bool> _keys;
    std::vector<bool> _keyPressed;
    std::vector<bool> _keyReleased;
};
