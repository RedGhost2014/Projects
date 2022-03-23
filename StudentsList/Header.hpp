#ifndef _MAINHEADER
#define _MAINHEADER

char* _cdecl strCopy(char* str);
char* _cdecl strGet();
int _cdecl strContain(const char* strToFind, const char* baseStr);
char* _cdecl strGetNumber();
void gotoxy(int x, int y);

void ListAction();
void AddStudentsAction();
void DeleteAction();
void ClearAction();
void PrintAction();

#endif // !_MAINHEADER
