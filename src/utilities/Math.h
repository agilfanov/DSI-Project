//
// Created by Arthur Gilfanov on 4/12/26.
//

#ifndef DSI_PROJECT_MATH_H
#define DSI_PROJECT_MATH_H
#include <vector>
#include <random>

/* Will contain code for calculations such as softmax and easy random number generation*/

class Math {

public:

    static int random_ind(int sz);

    static void softmax(std::vector<float>& vec);

    static void parallel_softmax(std::vector<float>& vec);
};




#endif //DSI_PROJECT_MATH_H