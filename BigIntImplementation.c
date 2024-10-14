#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 310

typedef struct BigInt_tag
{
    int *digits;
    int sign;                        //1 for positive numbers and -1 for negative numbers
    int length;                     
}Bigint;

Bigint stringtoBigInt(char *);
void BigInt_Print(Bigint*);
Bigint* BigInt_Subtraction(Bigint*,Bigint *);
Bigint * Subtract(Bigint*,Bigint *);
Bigint* BigInt_Addition(Bigint*,Bigint*);
Bigint* Compare_numbers(Bigint*,Bigint*);
Bigint* BigInt_Multiplication(Bigint*,Bigint*);

Bigint stringtoBigInt(char * num)
{
    Bigint b;
    int size=strlen(num);

    if(num[0]=='-') 
    {
        (b.sign)=-1;
        (b.length)=size-1;
        for(int i=0;i<size;i++)
        {
            num[i]=num[i+1];
        }
        size--;
    }
    else 
    {
        (b.sign)=1;
        (b.length)=size;
    }
    int i=0;
    (b.digits)=(int*)malloc(sizeof(int)*(b.length));
    size--;
    while(size>=0)
    {
        (b.digits[i])=num[size]-'0';           //This stores the bigint in the array in reverse order
        i++;
        size--;
    }
    return b;
}

void BigInt_Print(Bigint* b)                    //To print the big int
{
    int i=b->length-1;
    int flag=0;

    while(i>=0 && flag==0)
    {
        if(b->digits[i]==0)
        {
            i--;
        }
        else flag=1;
    }
    b->length=i+1;
	if((b->sign)==-1 && b->length!=0) printf("-");
	if(b->length!=0)
	{
    	for(int i=(b->length-1);i>=0;i--)
    	{
        	printf("%d",(b->digits[i]));
    	}
	}
	else printf("0");
}

Bigint* BigInt_Addition(Bigint* num1,Bigint* num2)                  //For addition of two numbers
{

    Bigint* sum;
    sum=(Bigint*)malloc(sizeof(Bigint));
    int c;
    if(num1->length>num2->length)
    {
        sum->digits=(int*)malloc(sizeof(int)*(num1->length+1));
    }
    else
    {
        sum->digits=(int*)malloc(sizeof(int)*(num2->length+1));
    }

    if(num1->sign==-1 && num2->sign==1)
    {
        if(num1==Compare_numbers(num1,num2)) 
        {
            sum=Subtract(num1,num2);
            sum->sign=-1;
        }
        else 
        {
            sum->sign=1;
            sum=Subtract(num2,num1);
        }
    }
    else if(num1->sign==1 && num2->sign==-1)
    {
		if(num2==Compare_numbers(num1,num2)) 
        {
            sum=Subtract(num2,num1);
            sum->sign=-1;
        }
        else 
        {
            sum->sign=1;
            sum=Subtract(num1,num2);
        }
    }
    else
    {
        c=0;
        int i=0,d;
        while(i<(num1->length) && i<(num2->length))
        {
            d=(num1->digits[i])+(num2->digits[i])+c;
            c=d/10;
            d=d%10;
            sum->digits[i]=d;
            i++;
        }
        while(i<num1->length)
        {
            d=(num1->digits[i])+c;
            c=d/10;
            d=d%10;
            sum->digits[i]=d;
            i++;
        }
        while (i<num2->length)
        {
            d=(num2->digits[i])+c;
            c=d/10;
            d=d%10;
            sum->digits[i]=d;
            i++;
        }
        if(c!=0)
        {
            sum->digits[i]=c%10;
            c=c/10;
            i++;
        }
        sum->length=i;
        sum->sign=num1->sign;
    }
    return sum;
}

Bigint* Compare_numbers(Bigint* num1,Bigint* num2)                         //For comparing two numbers during subtraction
{
    if(num1->length>num2->length) return num1;
    else if(num1->length<num2->length) return num2;

    else
    {
        for(int i=num1->length;i>0;i--)
        {
            if(num1->digits[i]>num2->digits[i]) return num1;
            else if(num1->digits[i]<num2->digits[i]) return num2;
        }
    }
    return num1;
}
Bigint * Subtract(Bigint* num1,Bigint * num2)                            //For subtracting two numbers independent of their values does num1-num2
{
    Bigint * sub=(Bigint*)malloc(sizeof(Bigint));
    sub->digits=(int *)malloc(sizeof(int)*(num1->length));
    int digit,i=0,borrow=0;

    while(i<num2->length)
    {
        digit=(num1->digits[i])-(num2->digits[i])-borrow;
        if (digit<0)
        {
            borrow=1;
            digit+=10;
        }
        else
        {
            borrow=0;
        }
        sub->digits[i]=digit;
        i++;
    }
    while (i<num1->length)
    {
        digit=(num1->digits[i])-borrow;
        if(digit<0)
        {
            borrow=1;
            digit+=10;
        }
        else
        {
            borrow=0;
        }
        sub->digits[i] = digit;
        i++;
    }
    sub->length=i;
    return sub;
}
Bigint* BigInt_Subtraction(Bigint* num1,Bigint * num2)                //For Subtracting 2 numbers
{
    Bigint * diff=(Bigint*)malloc(sizeof(Bigint));
    
    if( num1->length > num2->length )
    {
        diff->digits=(int*)malloc(sizeof(int)*(num1->length+1));
    }
    
    else
    {
        diff->digits=(int*)malloc(sizeof(int)*(num2->length+1));
    }

    if(num1->sign == -1 && num2->sign == 1)
    {
        num1->sign=1;
        diff=BigInt_Addition(num1,num2);
        diff->sign=-1;
        num1->sign=-1;
    }
    else if(num1->sign == 1 && num2->sign == -1)
    {
        num2->sign=1;
        diff=BigInt_Addition(num1,num2);
        diff->sign=1;
        num2->sign=-1;
    }
    else if(num1->sign==-1 && num2->sign==-1)
    {
        if(num1==Compare_numbers(num1,num2))
        {
            num1->sign=1;
            num2->sign=1;
            diff=Subtract(num1,num2);
            diff->sign=-1;
            num1->sign=-1;
            num2->sign=-1;
        }
        else
        {
            num1->sign=1;
            num2->sign=1;
            diff=Subtract(num2,num1);
            diff->sign=1;
            num1->sign=-1;
            num2->sign=-1;
        }
    }
    else
    {
        if(num1==Compare_numbers(num1,num2))
        {
            diff=Subtract(num1,num2);
            diff->sign=1;
        }
        else
        {
            diff=Subtract(num2,num1);
            diff->sign=-1;
        }
    }
    return diff;
}
Bigint* BigInt_Multiplication(Bigint *num1,Bigint* num2)            //For multiplying two numbers
{
    Bigint *ans;
    ans=(Bigint*)malloc(sizeof(Bigint));
    
    if( num1->sign == num2->sign )
    {
        ans->sign=1;
    }

    else 
    {
        ans->sign=-1;
    }

    ans->length=(num1->length)+(num2->length)+1;
    ans->digits=(int*)malloc(sizeof(int)*(ans->length));

    for(int i=0;i<ans->length;i++)
    {
        ans->digits[i]=0;
    }

    for(int i=0;i<num1->length;i++)
    {
        int carry=0,digit,j=0;
        for(j=0;j<num2->length;j++)
        {
            digit=(num1->digits[i]*num2->digits[j])+carry;
            carry=digit/10;
            ans->digits[i+j]=ans->digits[i+j]+(digit%10);

            if(ans->digits[i+j]>9)
            {
                ans->digits[i+j+1]++;
                ans->digits[i+j]=(ans->digits[i+j])%10;
            }
        }
        if(carry!=0)
        {
            ans->digits[i+j]=ans->digits[i+j]+(carry%10);
            if(ans->digits[i+j]>9)
            {
                ans->digits[i+j+1]++;
                ans->digits[i+j]=(ans->digits[i+j])%10;
            }
            carry=carry/10;
            j++;
        }
    }
    int i=ans->length-1;
    while(i>=0 && ans->digits[i]==0)
    {
        i--;
        (ans->length)--;
    }
    if(ans->length==0)
    {
        ans->sign=1;
        ans->length=1;
    }
    return ans;
}

int main()
{
    Bigint num1,num2;
    
    Bigint *ans,*n1,*n2;
    char *c1,*c2;
    c1=(char*)malloc(sizeof(char)*SIZE);
    c2=(char*)malloc(sizeof(char)*SIZE);

    printf("Welcome!This is the implementation of BigInt datatype with various operations for supporting 1024 bit integers\n");
    printf("Enter the first operand:");
    scanf("%s",c1);
    printf("Enter the second operand:");
    scanf("%s",c2);

    num1=stringtoBigInt(c1);
    n1=&num1;
    num2=stringtoBigInt(c2);
    n2=&num2;
    
    int choice;
    printf("Enter the operation you want:\n1.Addition\n2.Subtraction\n3.Multiplication");
    printf("\nEnter the choice:");
    for(int i=1;i<=3;i++)
    {
        scanf("%d",&choice);

    switch(choice)
    {
        case 1:
        ans=BigInt_Addition(n1,n2);
        printf("The addition of the two operands is:\n");
        BigInt_Print(ans);
        break;

        case 2:
        ans=BigInt_Subtraction(n1,n2);
        printf("The difference of the two operands is:\n");
        BigInt_Print(ans);
        break;

        case 3:
        ans=BigInt_Multiplication(n1,n2);
        printf("The multiplication of the two operands is:\n");
        BigInt_Print(ans);
        break;

        default: 
        printf("Invalid Input");
        break;
    }
    }
    free(ans);
    free(c1);
    free(c2);

    return 0;
}
