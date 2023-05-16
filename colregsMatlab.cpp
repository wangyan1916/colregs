//
// Created by rocky on 2023/5/15.
//

#include "COLREGs.hpp"
#include "mex.h"
#include <vector>
#include <string>
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // 检查输入参数数目和类型
    if (nrhs != 1 || !mxIsDouble(prhs[0]))
    {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "输入参数应为一个二维矩阵");
    }

    // 获取输入矩阵
    double *inputMatrix = mxGetPr(prhs[0]);
    int m = mxGetM(prhs[0]);
    int n = mxGetN(prhs[0]);

    std::vector<std::vector<double>> input(2, std::vector<double>(8,0));
    for (int i = 0; i < 16; i++)
    {
        if (i%2)
        {
            input[1][i/2] = *(inputMatrix + i);
        }else
        {
            input[0][i/2] = *(inputMatrix + i);
        }

    }
    // 创建输出布尔向量
    plhs[0] = mxCreateLogicalMatrix(2, 1);
    mxLogical *outputVector = mxGetLogicals(plhs[0]);
    COLREGs::Zheng judge(input);
    

    *outputVector = judge.getResult().at(0);
    *(outputVector + 1) = judge.getResult().at(1);

    std::string encounter; 
    switch (judge.getEncounter()) {
        case COLREGs::Zheng::MeetingType::OVERTAKE:
            encounter = "over take";
            break;
        case COLREGs::Zheng::MeetingType::HEAD_ON:
            encounter = "head on";
            break;
        case COLREGs::Zheng::MeetingType::CROSS:
            encounter = "cross";
            break;
        default:
            encounter = "null";
            break;
    }
    char * out = const_cast<char*>(encounter.c_str());
    plhs[1] = mxCreateString(out);

}