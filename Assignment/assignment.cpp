#include<bits/stdc++.h>
using namespace std;

set<char>character;
map<char,long long>pre_code;
map<char,string>encode_list;

char Huffman[1000];
struct node *temporary[1000];

struct node{
          char ch;
          long long pre_code;
          struct node *left,*right;
};

struct node* newNode(char a,long long f,struct node *l,struct node *r)
{
          struct node *temp=(struct node*)malloc(sizeof(struct node));
          temp->ch=a;
          temp->pre_code=f;
          temp->left=l;
          temp->right=r;

          return temp;
}

void encode(struct node *temp,string str)
{
          if(temp->left==NULL && temp->right==NULL)
          {
                    encode_list[temp->ch]=str;
                    cout<<temp->ch<<":"<<str<<endl;
                    return;
          }
          encode(temp->left,str+"0");
          encode(temp->right,str+"1");
}

void decode(string prefix,struct node *root)
{
          long long i;
          struct node *n=(struct node*)malloc(sizeof(struct node));
          n=root;
          for(i=0;prefix[i]!='\0';i++)
          {
                if(prefix[i]=='0'&&n->left!=NULL)
                {
                    n=n->left;
                }
                else if(prefix[i]=='1'&&n->right!=NULL)
                {
                    n=n->right;
                }
                if(n->ch!='\0')
                {
                    cout<<n->ch;
                    n=root;
                }
          }
}

void min_heapify(long long n,long long root)
{
          long long l=root*2+1,r=root*2+2,mini=root;

          if(l<n && temporary[mini]->pre_code>temporary[l]->pre_code)
          {
              mini=l;
          }
          if(r<n && temporary[mini]->pre_code>temporary[r]->pre_code)
          {
              mini=r;
          }
          if(temporary[mini]->pre_code!=temporary[root]->pre_code)
          {
                swap(temporary[mini],temporary[root]);
                min_heapify(n,mini);
          }
}
void insert_heap(long long len)
{
          while(len)
          {
            long long parent=(len-1)/2;
            if(temporary[parent]->pre_code>temporary[len]->pre_code)
                {
                    swap(temporary[parent],temporary[len]);
                    len=parent;
                }
            else
            {
                return;
            }
          }
}

void huffman()
{
          set<char>::iterator iterate;
          long long i=0,n=character.size();
          for(iterate=character.begin();iterate!=character.end();iterate++)
          {
                temporary[i]=newNode(*iterate,pre_code[*iterate],NULL,NULL);
                i++;
          }
          for(long long k=i/2-1;k>=0;k--)
                {
                    min_heapify(i,k);
                }
          while(n>1)
          {
                struct node *l=(struct node*)malloc(sizeof(struct node)),
                *r=(struct node*)malloc(sizeof(struct node));

                l=temporary[0];
                swap(temporary[0],temporary[n-1]);n--;
                min_heapify(n,0);

                r=temporary[0];
                swap(temporary[0],temporary[n-1]);
                min_heapify(n-1,0);

                temporary[n-1]=newNode('\0',l->pre_code+r->pre_code,l,r);
                insert_heap(n-1);
          }
          struct node *root=NULL;
          root=temporary[0];
          encode(root,"");
          string prefix;
          cout<<"Encoded message is:"<<endl;
          for(i=0;Huffman[i]!='\0';i++)
          {
                    cout<<encode_list[Huffman[i]];
                    prefix=prefix+encode_list[Huffman[i]];
          }
          cout<<endl;
          cout<<"The length of the code is:\n"<<prefix.size()<<endl;
          cout<<"Decoded message is:"<<endl;
          decode(prefix,root);
}

void freq(char Huffman[])
{
    int f[256]={0},i;
    for(i=0;Huffman[i]!='\0';i++)
    {
        f[Huffman[i]]++;
    }
    for(i=0;i<256;i++)
    {
        if(f[i]!=0)
        {
           cout<<char(i)<<" : "<<f[i]<<endl;
        }
    }
}

int main()
{
          FILE *file;
          file=fopen("file.txt","r");
          char a;
          long long i=0;
          while((a=fgetc(file))!=EOF)
          {
                    Huffman[i]=a;
                    pre_code[a]++;
                    character.insert(a);
                    i++;
          }
          cout<<"Frequency of the characters"<<endl;
          freq(Huffman);
          huffman();
          cout<<"\nThe text is:\n"<<Huffman<<endl;
}
