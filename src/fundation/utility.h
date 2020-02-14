/*****************************************************
���ƣ�utility.h
���ã��ṩһЩͨ�õĹ��ߣ���swap��move��forward�Ⱥ�����pair
*****************************************************/
#ifndef UTILITY_H
#define UTILITY_H
namespace TinySTL {

template<typename T>
void swap(T&a, T&b) 
{
	T temp = a;
	a = b;
	b = temp;
}

/**************************************************************************
//�ṹ��ģ�壺pair
//��first��second���ֱ�ȡ����һ���͵ڶ�������
**************************************************************************/
template<class _Ty1,
	class _Ty2>
	struct pair
{
	typedef _Ty1	first_type;
	typedef _Ty2	second_type;

	//��Ա����
	first_type		first;
	second_type		second;

	//���캯��
	pair()
		: first(_Ty1()),second(_Ty2())
		{
		}

	pair(const _Ty1& _Val1, const _Ty2& _Val2)
		: first(_Val1),second(_Val2)
		{
		}

	template<class _Other1,
		class _Other2>
		pair(const pair<_Other1, _Other2>& _Right)
		: first(_Right.first),second(_Right.second)
		{
		}
	~pair() = default;

};	//end of class pair


//���رȽϲ�����
template<class _Ty1,
	class _Ty2>
	bool operator==(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{	//���pair������Ԫ�ض���ȣ�������pair������Ϊ���
	return (_Left.first == _Right.first && _Left.second == _Right.second);
	}

template<class _Ty1,
	class _Ty2>
	bool operator!=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{
	return (!(_Left == _Right));
	}

template<class _Ty1,
	class _Ty2>
	bool operator<(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>&_Right)
	{	//���ȱȽ�first��first���ʱ�űȽ�second
	return (_Left.first < _Right.first ||
		(!(_Right.first < _Left.first) && _Left.second < _Right.second));
	}

template<class _Ty1,
	class _Ty2>
	bool operator>(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{
	return (_Right < _Left);
	}

template<class _Ty1,
	class _Ty2>
	bool operator<=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{
	return (!(_Right < _Left));
	}

template<class _Ty1,
	class _Ty2>
	bool operator>=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right)
	{
	return (!(_Left < _Right));
	}


template<class _Ty1,
	class _Ty2>
	pair<_Ty1, _Ty2> make_pair(const _Ty1& _Val1, const _Ty2& _Val2)
	{
	return pair<_Ty1, _Ty2>(_Val1, _Val2);
	}
}//namespace TinySTL
#endif // !UTILITY_H

