#include <iostream>
#include "arggregate.hpp"

// �W�v�J�e�S���̒�`�i����͍s���ƂɃJ�e�S���������B�j
typedef ::arggregate::ArggregateCategory(test)	Arggregate1;
typedef ::arggregate::ArggregateCategory(test)	Arggregate2;

typedef ::arggregate::Min<int, ::arggregate::Max<int> > MinMax;

void f1(Arggregate1::Decl< int, ::arggregate::Min<int> >::Type x=Arggregate1::Value< int, ::arggregate::Min<int> >(1000) )
{
	if( x.is_default() ) ::std::cout << x << ::std::endl;
}

void f2(Arggregate2::Decl< int, MinMax >::Type x1=Arggregate2::Value< int, ::arggregate::Min<int> >(-1)
	, Arggregate2::Decl< int, MinMax >::Type x2=Arggregate2::Value< int, ::arggregate::Max<int> >(1000) )
{
	::std::cout << x1 << ":" << x2 << ::std::endl;
}

int main(void)
{
	{
		::std::cout << "----- f1 ----- " << ::std::endl;

		f1();	// �W�v��� 0 �̂��� �ʏ�f�t�H���g�������n�����
		for( int i=10; i > 0; --i )
		{
			f1(i);	// �ʏ�g�p
		}
		f1();	// �W�v�������ʂ̍ŏ��l���f�t�H���g�����ƂȂ�
	}
	
	{
		::std::cout << "----- f2 ----- " << ::std::endl;
		
		f2();	// �W�v��� 0 �̂��� �ʏ�f�t�H���g�������n�����
		for( int i=10; i > 0; --i )
		{
			f2(i);	// �������̂ݎw��A�������ɂ��W�v���ʂ����f�����
		}
		f2();	// �W�v�������ʂ̍ŏ��l���f�t�H���g�����ƂȂ�
	}

	return 0;
}

