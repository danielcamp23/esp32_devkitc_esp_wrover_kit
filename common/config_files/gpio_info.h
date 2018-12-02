#ifndef _GPIO_INFO_H_
#define _GPIO_INFO_H_

#define GPIO_OUT_D18_18     18
#define GPIO_OUT_D19_19     19
#define GPIO_OUT_D21_21     21
#define GPIO_OUT_D22_22     22
#define GPIO_OUT_D23_23     23

#define GPIO_IN_D34_34      34
#define GPIO_IN_D35_35      35
#define GPIO_IN_D36_36      36
#define GPIO_IN_D37_37      37
#define GPIO_IN_D38_38      38
#define GPIO_IN_D39_39      39


#define GPIO_OUTPUT_PIN_SEL  (  (1ULL<<GPIO_OUT_D18_18) | (1ULL<<GPIO_OUT_D19_19) | \
                                (1ULL<<GPIO_OUT_D21_21) | (1ULL<<GPIO_OUT_D22_22) | \
                                (1ULL<<GPIO_OUT_D23_23) )

#define GPIO_INPUT_PIN_SEL  (   (1ULL<<GPIO_IN_D34_34) | (1ULL<<GPIO_IN_D35_35) | \
                                (1ULL<<GPIO_IN_D36_36) | (1ULL<<GPIO_IN_D37_37) | \
                                (1ULL<<GPIO_IN_D38_38) | (1ULL<<GPIO_IN_D39_39) )

#endif