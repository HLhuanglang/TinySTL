/*******************************************************************************************
���ƣ�type_traits
���ã���ȡ�ͱ�����ԣ��жϸ��ͱ��Ƿ���� Ĭ�Ϲ��캯����copy���캯������ֵ��������POD���͵ȡ�
˵����
	ʹ�õ���Ȼ��C99��׼�е�typedef��C++11��ʹ��using
*******************************************************************************************/
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

//������ֻ�� class object��ʽ�Ĳ����Ž��в����Ƶ���Ϊ���������ṩ�������ԡ�
struct __true_type {};
struct __false_type {};

template<class type>
struct __type_traits {
	typedef __false_type	has_trivial_default_constructor;
	typedef __false_type	has_trivial_copy_constructor;
	typedef __false_type	has_trivial_assignment_operator;
	typedef __false_type	has_trivial_destructor;
	typedef __false_type	is_POD_type;
};

/*�������C++�����ͱ�
	char��signed char�� unsigned char
	short��unsigned short
	int�� unsigned int
	long�� unsigned long
	float�� double��long double
	ÿ����Ա��ֵ���� __true_type ����ʾ��Щ�ͱ𶼿��Բ�������ٵķ�ʽ���п������߸�ֵ����*/

template<>
struct __type_traits<char> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<signed char> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<unsigned char> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<short> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<unsigned short> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<int> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<unsigned int> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};
template<>
struct __type_traits<long> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<unsigned long> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<float> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<double> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

template<>
struct __type_traits<long double> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};

//���ԭ��ָ����Ƶ� __type_traitsƫ�ػ��汾
template<class T>
struct __type_traits<T*> {
	typedef __true_type    has_trivial_default_constructor;
	typedef __true_type    has_trivial_copy_constructor;
	typedef __true_type    has_trivial_assignment_operator;
	typedef __true_type    has_trivial_destructor;
	typedef __true_type    is_POD_type;
};
	//�ж��Ƿ�Ϊ int ����
	template <class Type>
	struct __is_integer {
		typedef __false_type	is_integer;
	};

	template<> struct __is_integer<bool> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<char> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<signed char> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<unsigned char> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<short> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<unsigned short> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<int> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<unsigned int> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<long> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<unsigned long> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<long long> {
		typedef __true_type		is_integer;
	};

	template<> struct __is_integer<unsigned long long> {
		typedef __true_type		is_integer;
	};
#endif // !TYPE_TRAITS_H
