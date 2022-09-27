#pragma once
#include <iostream>
#include <cmath>
namespace mt::math
{

		template<typename T, int N, int M>
		struct MasWrapper
		{
			T mas[N][M];
		};

		template<typename T, int N, int M>
		class Matrix
		{
		public:
			Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = 0;
			}


			Matrix(const T mas[N][M])
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas[i][j];
			}


			Matrix(const MasWrapper<T, N, M>& mas)
			{
	#ifdef MY_DEBUG
				std::cout << "Constructor" << std::endl;
	#endif
				m_n = N;
				m_m = M;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mas.mas[i][j];
			}


			Matrix(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Copy constructor" << std::endl;
	#endif

				m_n = mat.m_n;
				m_m = mat.m_m;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.m_mat[i][j];
			}

			int getN() const { return m_n; }
			int getM() const { return m_m; }
			T get(int i, int j) const { return m_mat[i][j]; }
			void set(int i, int j, T data) { m_mat[i][j] = data; }



			Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "Operator =" << std::endl;
	#endif

				m_n = mat.getN();
				m_m = mat.getM();

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.get(i, j);

				return *this;
			}



			Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator+" << std::endl;
    #endif
                //Оператор сложения
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
				return tmp;
			}
            Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
            {
#ifdef MY_DEBUG
                std::cout << "operator-" << std::endl;
#endif
                //Оператор вычитания
                Matrix<T, N, M> tmp;
                for (int i = 0; i < m_n; i++)
                    for (int j = 0; j < m_m; j++)
                        tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
                return tmp;
            }



			Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
			{
	#ifdef MY_DEBUG
				std::cout << "operator*" << std::endl;
    #endif
                //оператор умножения
				Matrix<T, N, M> tmp;

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < mat.getM(); j++)
					{
						T sum = 0;
						for (int k = 0; k < m_m; k++)
							sum += m_mat[i][k] * mat.get(k, j);
						tmp.set(i, j, sum);
					}

				return tmp;
			}


			T det()//a11·a22 - a12·a21
            {
				if(m_n==m_m &&(m_n==2)|| m_n==3)
                {
                    if (m_n == 2)
                        return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];

                    T Det = 0;
                    Det += m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1]);
                    Det += -m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]);
                    Det += m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]);
                    return Det;
                }
                else if(m_n==m_m && m_n==1)
                    return m_mat[0][0];
                else { std::cout << "Too hard to calculate" << std::endl; return -1;}
			}



            Matrix<double,N,M> inverse()
            {
                {
                    if(m_n==m_m && (m_n==3))
                    {
                        T det = det();
                        T mas[2][2];
                        Matrix<double, N, M> tmp;
                        for (int i = 0; i < m_n; i++)
                            for (int j = 0; j < m_m; j++) {
                                mas[0][0] = m_mat[(j % 3 + 1) % 3][(i % 3 + 1) % 3];
                                mas[0][1] = m_mat[(j % 3 + 1) % 3][(i % 3 + 2) % 3];
                                mas[1][0] = m_mat[(j % 3 + 2) % 3][(i % 3 + 1) % 3];
                                mas[1][1] = m_mat[(j % 3 + 2) % 3][(i % 3 + 2) % 3];
                                if(j==1){ std::swap(mas[0][0],mas[1][0]);
                                    std::swap(mas[0][1],mas[1][1]);}
                                if(i==1){ std::swap(mas[0][0],mas[0][1]);
                                    std::swap(mas[1][0],mas[1][1]);}
                                tmp.set(i,j,double (pow(-1, i + j) * a_d(mas) /det));
                            }
                        return tmp;
                    }
                    else if(m_n==m_m && (m_n==2))
                    {
                        T det = det();
                        Matrix<double, N, M> tmp;
                        for(int i=0;i<m_n;i++)
                            for(int j=0;j<m_m;j++)
                            {
                                if(i!=j)
                                {tmp.set(i, j, pow(-1, i + j) * m_mat[i][j]/det);}
                                else{tmp.set(i, j, pow(-1, i + j) * m_mat[m_n-i-1][m_m-j-1]/det);}
                            }
                        return tmp;
                    }
                    else { std::cout << "This operate isn't working now" << std::endl;}
                }
            }
            Matrix<T,N,M> transposition()
            {
                Matrix<T,N,M> tmp;
                for(int i=0;i<m_n;i++)
                    for(int j=0;j<m_m;j++)
                        tmp.set(i,j,m_mat[j][i]);
                return tmp;
            }


			~Matrix()
			{
	#ifdef MY_DEBUG
				std::cout << "Destructor" << std::endl;
	#endif
			}


			friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);


			friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

		private:
			int m_n, m_m;
			T m_mat[N][M];
		};


		template<typename T, int N, int M>
		std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
		{
			for (int i = 0; i < mat.m_n; i++)
				for (int j = 0; j < mat.m_m; j++)
					in >> mat.m_mat[i][j];
			return in;
		}


		template<typename T, int N, int M>
		std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
		{
			out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
			for (int i = 0; i < mat.m_n; i++) {
				for (int j = 0; j < mat.m_m; j++)
					out << mat.m_mat[i][j] << " ";
				out << std::endl;
			}
			return out;
		}

		using Vec2i = Matrix<int, 2, 1>;
		using Vec2d = Matrix<double, 2, 1>;
		using Mat22i = Matrix<int, 2, 2>;
		using Mat22d = Matrix<double, 2, 2>;
}