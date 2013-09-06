#pragma once

namespace IS220 { namespace Estructuras { namespace Interfaces {
	
	template <typename TDato>
	class ICola {
	public:
		virtual bool Poner(const TDato& obj) = 0;
		
		virtual bool Sacar(TDato& ref) = 0;
	};
	
}}}
