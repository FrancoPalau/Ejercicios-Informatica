#include<stdio.h>
void duplicar(int *valor){
    *valor*=2;

}
int main(){
    int v;
    printf("Ingrese la variable v");
    scanf("%d",&v);
    duplicar(&v);
    printf("%d", v);
}
