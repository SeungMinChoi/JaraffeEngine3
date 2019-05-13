#pragma once

#include "JFTuple.h"
#include "JFTypeTraits.h"
#include <memory>

namespace JFFoundation
{
	template <class Function, class ReturnType, class... Params>
	class JFFunctionInvoker
	{
	public:
		JFFunctionInvoker(Function&& fn) : function(fn) {}
	
		ReturnType Invoke(Params... params)
		{
			function(params...);
		}
	
	private:
		Function* function;
	};

    // User-defined deduction guides
    template <class Function>
    class JFFunction
    {
    public:
        JFFunction(Function*);
    };

	template <class ReturnType, class... Params>
    class JFFunction<ReturnType(Params...)>
    { 
        using FunctionType = ReturnType(*)(Params...);

    public:
        JFFunction(FunctionType fn)
            : function(fn)
        {}

        void Invoke(Params... params)
        {
            function(params...);
        }

    private:
        FunctionType function;
    };

    //template <>
    //class JFFunction<ReturnType(*)(Params...)>
    //{
    //    //using FunctionType = ReturnType(*)(Params...);
    //
    //public:
    //    //JFFunction(FunctionType&& fn) : invoker(fn) {}
    //
    //    //ReturnType Invoke(Params... params)
    //    //{
    //    //    invoker(params...);
    //    //}
    //
    //private:
    //    //FunctionType invoker;
    //};
}