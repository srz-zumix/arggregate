#ifndef INCG_ARGGREGATE_H_
#define INCG_ARGGREGATE_H_

// define
#define ArggregateCategory(uniqename)	Category<__LINE__>

namespace arggregate
{

namespace detail
{

typedef class EOT
{
} EndOfTemplate, EndOfType;
	
/**
 * @brief	Aggregate Base
*/
class AggregateBase
{
protected:
	AggregateBase(void) : m_empty(true) {}
	void activate(void) { m_empty = false; }
public:
	bool empty(void) const { return m_empty; }
private:
	bool m_empty;
};

template<typename T>
class ValueType
{
	typedef T						value_type;
	typedef ValueType<value_type>	_Myt;
public:
	ValueType(void) {}
	ValueType(const value_type& rhs) : m_value(rhs) {}
	ValueType(const _Myt& rhs) : m_value(rhs.m_value) {}
	
	operator value_type& (void) { return m_value; }
	operator value_type (void) const { return m_value; }
	
	_Myt&	operator = (const value_type& rhs) { m_value = rhs; return *this; }
	_Myt&	operator = (const _Myt& rhs) { m_value = rhs.m_value; return *this; }
	
private:
	T m_value;
};

/**
 * @brief	デフォルト引数判別用の型
*/
template<typename T>
class DefaultArgument : public ValueType<T> 
{
public:
	DefaultArgument(void) {}
	DefaultArgument(const T& rhs) : ValueType<T>(rhs) {}
};

}

/**
 * @brief	カテゴリー
*/
template<int LINE>
class Category
{
	template<typename Aggregate>
	class Instance
	{
		static Aggregate	m_aggregate;
	public:
		static Aggregate&	GetInstance(void)	{ return m_aggregate; }
	};
	
	template<typename T, typename Aggregate>
	class AggregateList
	{
	public:
		static void add(const T& rhs)
		{
			Instance<typename Aggregate::InstantiateType>::GetInstance().add(rhs);
			AggregateList<T, typename Aggregate::NextType>::add(rhs);
		}
	};
	template<typename T>
	class AggregateList<T, detail::EOT>
	{
	public:
		static void add(const T&) {}
	};
	
public:
	/**
	 * @brief	型定義
	*/
	template<typename T, typename Aggregate>
	class Decl : public detail::ValueType<T>
	{
		typedef Decl<T, Aggregate>	_Myt;
	public:
		typedef _Myt	Type;
	public:
		Decl(const T& rhs) : detail::ValueType<T>(rhs), m_default(false)
		{
			AggregateList<T, Aggregate>::add(rhs);
		}
		Decl(const detail::DefaultArgument<T>& rhs) : detail::ValueType<T>(rhs), m_default(true)
		{
			// デフォルト引数の場合は集計しない
		}
		
	public:
		bool	is_default(void) const { return m_default; }
	private:
		bool	m_default;
	};
	
	/**
	 * @brief	デフォルト値の取得クラス
	*/
	template<typename T, typename SimpleAggregate>
	static detail::DefaultArgument<T> Value(const T& defalut_value)
	{
		return Instance<SimpleAggregate>::GetInstance().empty() ?
			defalut_value : static_cast<T>(Instance<SimpleAggregate>::GetInstance().value());
	}
};

template<int LINE>
template<typename Aggregate>
Aggregate	Category<LINE>::Instance<Aggregate>::m_aggregate;

/**
 * @brief	最小値
*/
template<typename T, typename Next=detail::EOT>
class Min : public detail::AggregateBase
{
	T m_value;
public:
	typedef Next	NextType;
	typedef Min<T, detail::EOT>	InstantiateType;

public:
	void	add(const T& value)
	{
		if( empty() || value < m_value )
		{
			m_value = value;
			activate();
		}
	}
	T		value(void) const { return m_value; }
};

/**
 * @brief	最大値
*/
template<typename T, typename Next=detail::EOT>
class Max : public detail::AggregateBase
{
	T m_value;
public:
	typedef Next	NextType;
	typedef Max<T, detail::EOT>	InstantiateType;

public:
	void	add(const T& value)
	{
		if( empty() || value > m_value )
		{
			m_value = value;
			activate();
		}
	}
	T		value(void) const { return m_value; }
};

}

#endif
