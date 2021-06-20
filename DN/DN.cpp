#include <iostream>
using namespace std;


//DN(2x2)のみ,四則演算(+-*/)のみ
class Matrix{
    double Mat[2][2];
public:
  ~Matrix(void) {};

  Matrix(void){
    Mat[0][0] = 0.0; Mat[0][1] = 0.0;
    Mat[1][0] = 0.0; Mat[1][1] = 0.0;
  }

  Matrix(const double obj) {
    Matrix temp;
    temp = obj;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        this->Mat[i][j] = temp.Mat[i][j];
      }
    }
  }


  inline const Matrix operator + (void) const {
    return *this;
  }

  const Matrix operator - (void) const {
    Matrix res;

    res = -1.0 * (*this);

    return res;
  }

  friend const Matrix operator * (const Matrix lhs,const Matrix rhs) {
    Matrix res;
    double temp;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        temp = 0.0;
        for (int k = 0; k < 2; k++) {
          temp += lhs.Mat[i][k]*rhs.Mat[k][j];
        }
        res.Mat[i][j] = temp;
      }
    }
    return res;
  }

  friend const Matrix operator * (const Matrix lhs,const double rhs) {
    Matrix res;
    Matrix temp = rhs;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        res.Mat[i][j] = lhs.Mat[i][j]*rhs;
      }
    }
    return res;
  }

  friend const Matrix operator * (const double lhs,const Matrix rhs) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        res.Mat[i][j] = lhs*rhs.Mat[i][j];
      }
    }
    return res;
  }


  friend const Matrix operator + (const Matrix lhs,const Matrix rhs) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        res.Mat[i][j] = lhs.Mat[i][j] + rhs.Mat[i][j];
      }
    }
    return res;
  }


  friend const Matrix operator - (const Matrix lhs,const Matrix rhs) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        res.Mat[i][j] = lhs.Mat[i][j] - rhs.Mat[i][j];
      }
    }
    return res;
  }


  friend const Matrix operator / (const Matrix lhs,const Matrix rhs) {
    Matrix res;
    Matrix rhs_inv;
    double temp;

    temp = rhs.Mat[0][0]*rhs.Mat[1][1] - rhs.Mat[0][1]*rhs.Mat[1][0];
    if (temp == 0) {
      cout << "逆行列が存在しない" << '\n';
      return res;
    } else {
      rhs_inv.Mat[0][0] = rhs.Mat[1][1];
      rhs_inv.Mat[0][1] = -rhs.Mat[0][1];
      rhs_inv.Mat[1][0] = -rhs.Mat[1][0];
      rhs_inv.Mat[1][1] = rhs.Mat[0][0];
      rhs_inv = (1.0/temp) * rhs_inv;
    }
    res = lhs * rhs_inv;

    return res;
  }


  Matrix operator = (const Matrix obj) {
    Matrix res;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        this->Mat[i][j] = obj.Mat[i][j];
      }
    }
    return *this;
  }

  Matrix operator = (const double obj) {
    Matrix res;
    this->Mat[0][0] = obj;
    this->Mat[1][1] = obj;
    return *this;
  }

  Matrix Inverse(void){
    Matrix res;
    double temp;

    temp = this->Mat[0][0]*this->Mat[1][1] - this->Mat[0][1]*this->Mat[1][0];
    if (temp == 0) {
      cout << "逆行列が存在しない" << '\n';
      return *this;
    } else {
      res.Mat[0][0] = this->Mat[1][1];
      res.Mat[0][1] = -this->Mat[0][1];
      res.Mat[1][0] = -this->Mat[1][0];
      res.Mat[1][1] = this->Mat[0][0];
      res = (1.0/temp)*res;
    }
    return res;
  }



  void DualNumber(){
    Mat[0][0]=0.0; Mat[0][1]=1.0;
    Mat[1][0]=0.0; Mat[1][1]=0.0;
  }

  void IdentityMatrix(){
    Mat[0][0]=1.0; Mat[0][1]=0.0;
    Mat[1][0]=0.0; Mat[1][1]=1.0;
  }

  void Zero(){
    Mat[0][0]=0.0; Mat[0][1]=0.0;
    Mat[1][0]=0.0; Mat[1][1]=0.0;
  }

  double GetDN() {
    return Mat[0][1];
  }

  void show(){
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        cout << Mat[i][j];
        if (j!=1) {
          cout << ",";
        }
      }
      cout << '\n';
    }
  }
};

Matrix Matrix_inv(Matrix obj) {
  Matrix res;
  res = obj.Inverse();
  return res;
}


double func(double x) {
  double res;
  res = 4*x*x + 2*x + 3;
  return res;
}

double differential_func(Matrix x) {
  Matrix res;
  res = Matrix(4.0)*x*x + Matrix(2.0)*x + Matrix(3.0);
  return res.GetDN();
}

 // main 関数
int main(){
  double x = 2.0;
  double fx,fdx;
  Matrix Dnum;
  Matrix res;

  Dnum.DualNumber();
  Dnum = Dnum + Matrix(x);

  fx  = func(x);
  fdx = differential_func(Dnum);

  cout << "f(x)=4x*x + 2x + 3" << '\n';
  cout << "x=" << x << '\n';
  cout << "f(x)=" << fx << '\n';
  cout << "f'(x)=" << fdx << '\n';




  return 0;
}
