
#ifndef OCTEOTOS_CORE_V3_SEMVER_HH
#define OCTEOTOS_CORE_V3_SEMVER_HH


namespace oct::core::v3
{


class Semver
{
public:
    enum class Tokens : int
    {//https://www.charset.org/utf-8,https://www.asciitable.com/,https://www.rapidtables.com/code/text/ascii-table.html
        command = -100,
        eoi,//end of input
        none,
        //ASCII>>>
        NUL = 0,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        TAB,
        LF,
        VT,
        FF,
        CR,
        SO,
        SI,
        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        EM,
        SUB,
        ESC,
        FS,
        GS,
        RS,
        US = 31,
        space,
        exclamation_mark,
        double_quote,
        symbol_numbers,
        symbol_money,
        percen,
        ampersan,
        single_quote,
        parenthesis_open,
        parenthesis_close,
        asterisk,
        plus,
        minus,
        dot,
        symbol_diagonal,
        digit_0		= 48,
        digit_1,
        digit_2,
        digit_3,
        digit_4,
        digit_5,
        digit_6,
        digit_7,
        digit_8,
        digit_9,
        symbol_column,
        semicolumn,
        less,
        equal,
        grater,
        question,
        arroba,
        //>>upper case
        char_A		= 65,
        char_B,
        char_C,
        char_D,
        char_E,
        char_F,
        char_G,
        char_H,
        char_I,
        char_J,
        char_K,
        char_L,
        char_M,
        char_N,
        char_O,
        char_P,
        char_Q,
        char_R,
        char_S,
        char_T,
        char_U,
        char_V,
        char_W,
        char_X,
        char_Y,
        char_Z,
        //>>

        //>>>
        char_a		=	97,
        char_b,
        char_c,
        char_d,
        char_e,
        char_f,
        char_g,
        char_h,
        char_i,
        char_j,
        char_k,
        char_l,
        char_m,
        char_n,
        char_o,
        char_p,
        char_q,
        char_r,
        char_s,
        char_t,
        char_u,
        char_v,
        char_w,
        char_x,
        char_y,
        char_z,

        EuroSign	= 218,
        //>>>Extended ASCII






        y_Diaeresis = 255,//ÿ
        //>>>UTF-8
        a_Macron	= 256,

        s_Coptic	= 999,
        //Inicode >>>


        //>>>Tokens
        base	= 0x110000,

        number,
        string,


    };
};

}


#endif
