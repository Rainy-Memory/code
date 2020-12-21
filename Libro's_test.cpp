//
// Created by Libro on 2020/12/17.
//

#include <iostream>
#include <cstring>

//#define ASCII
//#define const_char
#define c_string
using namespace std;

int main() {
#ifdef ASCII
    cout << int('\0') << ' ' << int(' ') << ' ' << int('\n') << ' ' << int('\r') << endl;
#endif
#ifdef const_char
    {
        char *a = "Libro";
        a = "abcdefg";
        a = "abc";
        cout << a[0] << '\n';
        //a[0]='c'; error
    }
#endif
#ifdef get_getline
    {
        {
            char a[] = {'H', 'E', 'L', 'L', 'O', '\0'};
            cout << a << endl;
            char b[] = "HELLO";
            cout << b << endl;
        }
        char c[10], d[10];
        cin.getline(c, 5, '.');//delete ',' in istream
        cout << cin.fail();
        cin.clear();
        cout << cin.fail();
        cin.get(d, 5, ',');
        cout << c << ' ' << d << endl;
        cin.clear();
        char ch1;
        cin.get(ch1);
        cout << ch1 << endl;
    }
#endif
#ifdef c_string
    {
        char* a1;
        char c1[20]="Libro***";
        char c2[20]="Rainy_memory";
        char c3[20];
        //strcpy and strncpy
        a1=strcpy(c3,c2);
        cout<<*a1<<' '<<a1<<endl;
        a1=strncpy(c3,c2,5);
        cout<<*a1<<' '<<a1<<endl;
        a1[5]='\0';
        cout<<a1<<endl;
        //strcat and strncat
        char* a2;
        a2=strcat(c2," and ");
        a2=strncat(c2,c1,5);
        cout<<a2<<'\n';
        //strlen
        cout<<strlen(a1)<<' ';
        a1[1]='\0';
        cout<<strlen(a1)<<'\n';
        //strcmp and strncmp
        cout<<strcmp("Libro",c1)<<' '<<strcmp(c1,"Libro")<<' '<<strncmp(c1,"Libro",5)<<endl;
        //strchr strrchr strstr
        cout<<strchr(c1,'*')<<' '<<strrchr(c1,int('*'))<<' '<<strstr(c1,"**")<<' '<<endl;
        cout<<(void*)strchr(c1,'*')<<' '<<(void*)strrchr(c1,int('*'))<<' '<<(void*)strstr(c1,"**")<<endl;
    }
#endif
    return 0;
}