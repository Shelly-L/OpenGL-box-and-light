#pragma once

//�Ƿ��鿪��
#ifdef DEBUG
#define GL_CALL(func) func;checkError();
#else
#define GL_CALL(func) func;
#endif

void checkError();