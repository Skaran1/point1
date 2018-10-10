#include <stdio.h>
#include <math.h>
const int N=18;
void Array (float V1[],float A1[], float L1[],float D1[])
{
	FILE*f1=fopen("lab.txt","r");
	for (int i=0;i<=(N-1);i++)
	{
		fscanf(f1,"%f %f %f %f",&V1[i],&A1[i],&L1[i],&D1[i]);
	}
	fclose(f1);
}
void Calculation (float V1[],float A1[], float L1[],float D1[], float p1[])
{
	FILE*f2=fopen("labrez.txt","w");
	for (int i=0;i<=(N-1);i++)
	{
		p1[i]=V1[i]/A1[i]/L1[i]*(3,14)/4*D1[i]*D1[i]*1000000;
		fprintf(f2,"Эксперимент №%2i, p=%f\n",i,p1[i]);
	}
	fclose(f2);
}
void Middle(float p[],float * average1)
{
	float summ=0;
	for (int i=0;i<=(N-1);i++)
	{
		summ=summ+p[i];
	}
	*average1=summ/N;
}
void Write_down_f2 (float*average1,float Sigma_final)
{
  FILE*f2=fopen("labrez.txt","a");
  fprintf(f2,"\nРезультат р=%f±%f",*average1,Sigma_final);
  fclose(f2);
}
void Quadratic_mean (float a[],float * Sigma1)
{
  *Sigma1=0;
  float average2;
  Middle (a,&average2);
  for (int i=0;i<=(N-1);i++)
  {
    *Sigma1=*Sigma1+(a[i]-average2)*(a[i]-average2);
  }
  *Sigma1=sqrt(*Sigma1/N/(N-1));
}
float Sigma_error(float avV,float avA,float avL,float avD,float sigV,float sigA,float sigL,float sigD)
{
	return sqrt((sigV/avV)*(sigV/avV)+(sigA/avA)*(sigA/avA)+(sigL/avL)*(sigL/avL)+4*(sigD/avD)*(sigD/avD));
}
int main()
{
  float V[18],A[18],L[18],D[18],p[18];
	float average,average_V,average_A,average_L,average_D,Sigma_V,Sigma_A,Sigma_L,Sigma_D,Sigma_p;
  Array(V,A,L,D);
  Calculation(V,A,L,D,p);
	Middle (p,&average);
  Middle (V,&average_V);
	Middle (A,&average_A);
	Middle (L,&average_L);
	Middle (D,&average_D);
	Quadratic_mean(V,&Sigma_V);
	Quadratic_mean(A,&Sigma_A);
	Quadratic_mean(L,&Sigma_L);
	Quadratic_mean(D,&Sigma_D);
	Sigma_p=Sigma_error(average_V,average_A,average_L,average_D,Sigma_V,Sigma_A,Sigma_L,Sigma_D);
  Write_down_f2 (&average,Sigma_p);
}
