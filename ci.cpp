#include<stdio.h>
#include<string.h>

int numOfChar=0; 
int numOfLine=1;//����ͳ��
int numOfWord=0; //ͳ�Ƶ��ʸ��� 
int pos=0;//�ַ���λ��ָ��
char c;
char str[100001]; 

void connect(char c)//�ַ����ӵ�str�� 
{
	str[pos]=c;
	pos++;
}

void retract()//str���ˣ���c�ÿ� 
{
	pos--;
	c=' ';
} 

int isDigit(char c)//�Ƿ�Ϊ���� 
{
	if(c>='0' && c<='9')
         return 1;
    else return 0;
}

int isLetter(char c) //�Ƿ�Ϊ��ĸ 
{
    if((c>='a' && c<='z')||(c>='A' && c<='Z'))    
        return 1;
    else return 0; 
}

char getChar()
{
	scanf("%c",&c);
	if(c == '$')
	{
         printf("�ʷ���������");
         numOfChar--;
	}
	numOfChar++;
	return c;
}

void isBlank()
{
	while(c==' '||c=='\t'||c=='\n'||c=='\b')
	{
		if(c=='\n') numOfLine++;
		getChar(); 
	}
}

int isBound(char c)//�Ƿ�Ϊ�ֽ�� 
{
	 if(c=='.' || c=='{' || c=='}' || c=='[' ||
	 	c==';' || c=='#' || c=='\\' || c=='\'' ||
	    c==']' || c=='(' || c==')' || c==',' || 
		c=='\"' || c=='\?' || c==':')
         return 1;
     else return 0;
} 

int isKey(char str[])//�ж��Ƿ�Ϊ�ؼ��� 
{
	if((strcmp(str,"auto")==0)||(strcmp(str,"auto")==0)||
		(strcmp(str,"case")==0)||(strcmp(str,"char")==0)||
		(strcmp(str,"const")==0)||(strcmp(str,"continue")==0)||
		(strcmp(str,"default")==0)||(strcmp(str,"double")==0)||
		(strcmp(str,"do")==0)||(strcmp(str,"else")==0)||
		(strcmp(str,"enum")==0)||(strcmp(str,"extern")==0)||
		(strcmp(str,"float")==0)||(strcmp(str,"for")==0)||
		(strcmp(str,"goto")==0)||(strcmp(str,"if")==0)||
		(strcmp(str,"int")==0)||(strcmp(str,"long")==0)||
		(strcmp(str,"register")==0)||(strcmp(str,"return")==0)||
		(strcmp(str,"short")==0)||(strcmp(str,"signed")==0)||
		(strcmp(str,"sizeof")==0)||(strcmp(str,"static")==0)||
		(strcmp(str,"struct")==0)||(strcmp(str,"switch")==0)||
		(strcmp(str,"typedef")==0)||(strcmp(str,"union")==0)||
		(strcmp(str,"unsigned")==0)||(strcmp(str,"void")==0)||
		(strcmp(str,"volatile")==0)||(strcmp(str,"while")==0)
		)
	return 1;
	else return 0;
	
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	getChar();
	isBlank();
	while(1)
	{
		if(c=='$')
			break;
		//�ж��Ƿ��Ǳ�ʶ����������Ϲؼ��ֱ�׼��Ϊ�ؼ��֣� 
		else if(isLetter(c))
      	{
          pos=0;
          while(isLetter(c)||isDigit(c)||c=='_')
          {
               connect(c);//������ϾͰ������������� 
               getChar();//��������� 
          }
          str[pos++]='\0';//��һ�������� 
          if(isKey(str)==1) 
              printf("%s\t�ؼ���\n",str);
          else printf("%s\t��ʶ��\n",str);
          numOfWord++; 
          isBlank();
      	}
      	//�ж��Ƿ�Ϊ���� 
      	else if(isDigit(c))     
      	{
          pos=0; 
          while(isDigit(c))
          {
               connect(c);
               getChar();
          }
          if(isLetter(c))
          { 
               str[0]='\0';
               printf("��%d�������ֺ����ĸ�ķǷ��ַ�\n",numOfLine); 
               while(isLetter(c))
                   getChar();  
          }
          str[pos++]='\0';
          if(str[0]!='\0')
               printf("%s\t����\n",str);
          numOfWord++; 
          isBlank();                                                      
      	}
      	//�����ʶ�� 
      	else if(c=='+') //+,++,+=
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='+'||c=='=')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  isBlank();
              }          
          }
          
          else if(c=='-') //-,--,-=
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='-'||c=='=')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  isBlank();
              }
          }          
          
          else if(c=='*' || c=='%' || c=='!' || c=='>' || c=='<' || c=='=') 
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='=')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  isBlank();
              }
          }          
          
          else if(c=='&') // &&
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='&')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }
              else
			  //��Ŀ����� 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar(); 
                  isBlank();
              } 
          } 
         
          else if(c=='|') // ||
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='|')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar(); 
                  isBlank();
              } 
          } 
          
          else if(c=='/')
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='=')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  getChar();
                  isBlank();
              }    
			  //ע��     
              else if(c=='/')
              {
                  retract(); 
                  while(c!='\n'&&c!='$') 
                      getChar();
                  isBlank(); //�¼ӵ� 
              } 
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t�����\n",str);
                  isBlank();
              }                   
          }
          //�ֽ��         
          else if(isBound(c))     
          {
              pos=0; 
              connect(c);
              str[pos++]='\0';
              printf("%s\t�ֽ��\n",str);
              getChar();
              isBlank();                                                       
          } 
          //���ʲô�����������Ͼ��ǷǷ��ַ� 
          else 
          {
               printf("��%d���зǷ��ַ�\n",numOfLine); 
               getChar();  
               isBlank();
          }
	}
	printf("\n\n\n\n\n\n");
	printf("����Ϊͳ�ƽ����\n");
	printf("����Ϊ%d\n",numOfLine);
	printf("������Ϊ%d\n",numOfWord);
	printf("�ַ���Ϊ%d\n",numOfChar);
	return 0;
}
