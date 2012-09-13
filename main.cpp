#include <iostream>
#include "arggregate.hpp"

// 集計カテゴリの定義（現状は行ごとにカテゴリ化される。）
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

		f1();	// 集計情報 0 のため 通常デフォルト引数が渡される
		for( int i=10; i > 0; --i )
		{
			f1(i);	// 通常使用
		}
		f1();	// 集計した結果の最小値がデフォルト引数となる
	}
	
	{
		::std::cout << "----- f2 ----- " << ::std::endl;
		
		f2();	// 集計情報 0 のため 通常デフォルト引数が渡される
		for( int i=10; i > 0; --i )
		{
			f2(i);	// 第一引数のみ指定、第二引数にも集計結果が反映される
		}
		f2();	// 集計した結果の最小値がデフォルト引数となる
	}

	return 0;
}

