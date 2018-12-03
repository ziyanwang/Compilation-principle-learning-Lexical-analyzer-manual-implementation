#include<stdio.h>
#include<string.h>

int numOfChar=0; 
int numOfLine=1;//行数统计
int numOfWord=0; //统计单词个数 
int pos=0;//字符串位置指针
char c;
char str[100001]; 

void connect(char c)//字符连接到str中 
{
	str[pos]=c;
	pos++;
}

void retract()//str回退，将c置空 
{
	pos--;
	c=' ';
} 

int isDigit(char c)//是否为数字 
{
	if(c>='0' && c<='9')
         return 1;
    else return 0;
}

int isLetter(char c) //是否为字母 
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
         printf("词法分析结束");
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

int isBound(char c)//是否为分界符 
{
	 if(c=='.' || c=='{' || c=='}' || c=='[' ||
	 	c==';' || c=='#' || c=='\\' || c=='\'' ||
	    c==']' || c=='(' || c==')' || c==',' || 
		c=='\"' || c=='\?' || c==':')
         return 1;
     else return 0;
} 

int isKey(char str[])//判断是否为关键字 
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
		//判断是否是标识符（如果符合关键字标准即为关键字） 
		else if(isLetter(c))
      	{
          pos=0;
          while(isLetter(c)||isDigit(c)||c=='_')
          {
               connect(c);//如果符合就把他们连接起来 
               getChar();//继续往后读 
          }
          str[pos++]='\0';//放一个结束符 
          if(isKey(str)==1) 
              printf("%s\t关键字\n",str);
          else printf("%s\t标识符\n",str);
          numOfWord++; 
          isBlank();
      	}
      	//判断是否为数字 
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
               printf("第%d行有数字后加字母的非法字符\n",numOfLine); 
               while(isLetter(c))
                   getChar();  
          }
          str[pos++]='\0';
          if(str[0]!='\0')
               printf("%s\t数字\n",str);
          numOfWord++; 
          isBlank();                                                      
      	}
      	//运算符识别 
      	else if(c=='+') //+,++,+=
          {
              pos=0;
              connect(c);
              getChar();
              if(c=='+'||c=='=')
              {
                  connect(c);
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
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
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
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
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
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
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }
              else
			  //单目运算符 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
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
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
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
                  printf("%s\t运算符\n",str);
                  getChar();
                  isBlank();
              }    
			  //注释     
              else if(c=='/')
              {
                  retract(); 
                  while(c!='\n'&&c!='$') 
                      getChar();
                  isBlank(); //新加的 
              } 
              else 
              {
                  str[pos++]='\0';
                  printf("%s\t运算符\n",str);
                  isBlank();
              }                   
          }
          //分界符         
          else if(isBound(c))     
          {
              pos=0; 
              connect(c);
              str[pos++]='\0';
              printf("%s\t分界符\n",str);
              getChar();
              isBlank();                                                       
          } 
          //如果什么都不属于以上就是非法字符 
          else 
          {
               printf("第%d行有非法字符\n",numOfLine); 
               getChar();  
               isBlank();
          }
	}
	printf("\n\n\n\n\n\n");
	printf("如下为统计结果：\n");
	printf("行数为%d\n",numOfLine);
	printf("单词数为%d\n",numOfWord);
	printf("字符数为%d\n",numOfChar);
	return 0;
}
