#pragma once

namespace JFFoundation
{
	template <class... Types>
	struct JFTupleElement{};

	template <class T, class... Types>
	struct JFTupleElement<T, Types...> : public JFTupleElement<Types...>
	{
		using Type = T;
		using ClassType = JFTupleElement<T, Types...>;

		JFTupleElement() {}
		JFTupleElement(Type&& _data, Types&&... args)
			: data(_data)
			, JFTupleElement<Types...>(std::forward<Types>(args)...) {}

		Type data;
	};

	template <size_t Index, class... Types>
	struct SequenceTupleElement;

	template <class T, class... Types>
	struct SequenceTupleElement<0, T, Types...>
	{
		using Type = T;
		using ClassType = typename JFTupleElement<T, Types...>;
	};

	template <size_t Index, class T, class... Types>
	struct SequenceTupleElement<Index, T, Types...>
		: public SequenceTupleElement<Index - 1, Types...>
	{};

	template <class... Types> 
	class JFTuple
	{
	public:
		enum { Count = 1 + sizeof...(Types) };

		JFTuple() {}
		JFTuple(Types&&... args) : elements(std::forward<Types>(args)...) {}

		template <size_t Index>
		typename SequenceTupleElement<Index, Types...>::Type& Item()
		{
			return (static_cast<typename SequenceTupleElement<Index, Types...>::ClassType&>(elements)).data;
		}

	private:
		JFTupleElement<Types...> elements;
	};
}