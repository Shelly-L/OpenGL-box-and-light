#pragma once

//是否检查开关
#ifdef DEBUG
#define GL_CALL(func) func;checkError();
#else
#define GL_CALL(func) func;
#endif

void checkError();