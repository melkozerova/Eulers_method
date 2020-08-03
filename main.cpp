#include <fstream>
#include <math.h>
using namespace std;

int main(){
    ofstream Leap_Out("Leap_Out.txt", ios::out); //Файл для записи решений: первый столбец - время,
                                                 //второй - численное решение, третий - аналитическое решение;
	ofstream Abs_err("Abs_Err.txt", ios::out);   // Файл для записи ошибок: первый столбец - время
	                                             // второй - ошибка вычислений
	Leap_Out.setf(ios::fixed);
	Abs_err.setf(ios::fixed);
	
    double U_0 = 173.0 / 30.0; // Начальное значение функции U
    double Leap_Step = 0.2; // Шаг по времени 
    double Interval = 20; // Временной интервал
    
    double U_Euler = U_0; 
	double V_Euler = 0; // Начальное значение функции производной функци U (скорость)                                
    double Euler_Step = Leap_Step / 5.0; // Шаг схемы Эйлера                       
    
    for(double t = 0; t < Leap_Step; t += Euler_Step){      
        V_Euler += -1 * U_Euler * Euler_Step;
        U_Euler += V_Euler * Euler_Step;
    }
    
    //Схема с перешагиваем   
    double U_Prev = U_0;                                     
    double U_Now = U_Euler;  /*U_0*cos(Leap_Step); */                        
    double U_Next;
    double V_Prev = 0; 
    double V_Now = V_Euler;  /*-U_0*sin(Leap_Step); */
    double V_Next;
    
    // Вывод в файл       
    for (double t = Leap_Step; t <= Interval; t += Leap_Step) {
       Abs_err << t << " " << fabs(U_0 * cos(t) - U_Now) << endl;
       Leap_Out << t << " " << U_Now << " " << U_0 * cos(t) << endl;
       
       U_Next = U_Prev + V_Now * 2 * Leap_Step;
       V_Next = V_Prev - U_Now * 2 * Leap_Step;
       
       U_Prev = U_Now;
       U_Now = U_Next; 
       
       V_Prev = V_Now;
       V_Now = V_Next;
    }
    
    return 0;
}

