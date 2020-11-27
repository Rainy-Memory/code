#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{
    
    struct NODE {
        int c=-1;
        NODE* next=NULL;
    };
    
    NODE *head = nullptr;
    int len = 0;
    
    void init() {
        // TODO
    }
    NODE* move(int i) {
        // TODO
        
    }
    void insert(int i, int x) {
        if(i>len)return;
        if(len==0)
        {
            head=new NODE;
            head->c=x;
            head->next=head;
        }else
        {
            NODE* end=head;
            for(int j=0;j<len-1;j++)
            {
                end=end->next;
            }
            if(i==0)
            {
                NODE* now=head;
                head=new NODE;
                head->next=now;
                head->c=x;
                end->next=head;
                len++;
                return;
            }
            NODE* Now=head;
            NODE* Before=end;
            for(int j=0;j<i;j++)
            {
                Now=Now->next;
                Before=Before->next;
            }
            Before->next=new NODE;
            Before->next->c=x;
            Before->next->next=Now;
        }
        len++;
    }
    void remove(int i) {
        if(i>=len)return;
        NODE* Remove=head;
        NODE* After=head;
        After=After->next;
        NODE* end=head;
        for(int j=0;j<len-1;j++)
        {
            end=end->next;
        }
        NODE* Before=end;
        for(int j=0;j<i;j++)
        {
            Before=Before->next;
            Remove=Remove->next;
            After=After->next;
        }
        if(Remove==head)
        {
            head=Remove->next;
            end->next=head;
            delete Remove;
        }else
        {
            Before->next=After;
            delete Remove;
        }
        len--;
    }
    void remove_insert(int i) {
        if(i>=len)return;
        NODE* Remove=head;
        NODE* After=head;
        After=After->next;
        NODE* end=head;
        for(int j=0;j<len-1;j++)
        {
            end=end->next;
        }
        NODE* Before=end;
        for(int j=0;j<i;j++)
        {
            Before=Before->next;
            Remove=Remove->next;
            After=After->next;
        }
        int tem_c;
        if(Remove==head)
        {
            head=Remove->next;
            return;
        }else
        {
            Before->next=After;
            tem_c=Remove->c;
            delete Remove;
            end->next=new NODE;
            end->next->c=tem_c;
            end->next->next=head;
        }
        
    }
    void get_length() {
        cout<<len<<'\n';
    }
    void query(int i) {
        if(i>=len)
        {
            cout<<-1<<'\n';
            return;
        }else
        {
            NODE* query=head;
            for(int j=0;j<i;j++)
            {
                query=query->next;
            }
            cout<<query->c<<'\n';
        }
    }
    void get_max() {
        NODE* now=head;
        int max=-1;
        for(int j=0;j<len;j++)
        {
            if(max==-1)
            {
                max=now->c;
            }else
            {
                if(max<now->c)max=now->c;
            }
            now=now->next;
        }
        cout<<max<<'\n';
    }
    void clear() {
        NODE* next;
        for(int i=0;i<len;i++)
        {
            next=head->next;
            delete head;
            head=next;
        }
        len=0;
    }
    
}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}