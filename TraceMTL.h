/*
  TraceMTL.h
     
  C++ code solution for trace out all data in Wavefront MTL Parser class
  
  MIT License

  Copyright (c) 2023 Stefan Falcon Johnsen

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

  Author: Stefan Falcon Johnsen
  Email: stefan.johnsen@outlook.com
  Date: 24.04.2023
 */

#pragma once

#include "WavefrontMTL.h"

#include <iostream>

namespace mtl
{
	template <typename T>
	void trace(const Value<T>& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << item.value;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const Value<bool>& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " ";

		if( item )
			std::cout << "on";
		else
			std::cout << "off";

		if( end_line ) std::cout << std::endl;
	}

	template <typename T>
	void trace(const std::string& label, const Value<T>& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " " << item.value;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const xyz& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " xyz " << item.x << " " << item.y << " " << item.z;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const rgb& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " " << item.r << " " << item.g << " " << item.b;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const Model& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " " << item.base << " " << item.gain;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const uvw& item, const bool end_line = true)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " " << item.u << " " << item.v << " " << item.w;

		if( end_line ) std::cout << std::endl;
	}

	inline void trace(const std::string& label, const Opacity& item)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label;

		if( item.halo ) std::cout << " -halo";

		std::cout << " " << item.d << std::endl;
	}

	inline void trace(const std::string& label, const Spectral& item)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " spectral " << item.file << " " << item.factor;
	}

	inline void trace(const std::string& label, const Color& item)
	{
		if( !item.isParsed() ) return;

		trace(label, item.color);
		trace(label, item.color_space);
		trace(label, item.spectral);
	}

	inline void trace(const std::string& label, const Texture& item)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label;

		trace("-blendu", item.blendu, false);
		trace("-blendv", item.blendv, false);
		trace("-clamp", item.clamp, false);
		trace("-cc", item.cc, false);
		trace("-bm", item.bm, false);
		trace("-boost", item.boost, false);
		trace("-texres", item.texres, false);
		trace("-mm", item.mm, false);
		trace("-o", item.o, false);
		trace("-s", item.s, false);
		trace("-t", item.t, false);
		trace("-imfchan", item.imfchan, false);

		trace(item.file);
	}

	inline void trace(const std::string& label, const Reflection& item)
	{
		if( !item.isParsed() ) return;

		std::cout << " " << label << " -type";

		trace("sphere", item.sphere);
		trace("cube_top", item.cube_top);
		trace("cube_bottom", item.cube_bottom);
		trace("cube_front", item.cube_front);
		trace("cube_back", item.cube_back);
		trace("cube_left", item.cube_left);
		trace("cube_right", item.cube_right);
	}

	inline void trace(const Material& material)
	{
		std::cout << std::endl;

		trace("newmtl", material.name);

		trace("Ka", material.Ka);
		trace("Kd", material.Kd);
		trace("Ks", material.Ks);
		trace("Ke", material.Ke);
		trace("map_Kd", material.map_Kd);
		trace("map_Ka", material.map_Ka);
		trace("map_Ks", material.map_Ks);
		trace("map_Ke", material.map_Ke);
		trace("map_Ns", material.map_Ns);
		trace("map_Pr", material.map_Pr);
		trace("map_Pm", material.map_Pm);
		trace("map_Ps", material.map_Ps);
		trace("map_d", material.map_d);
		trace("map_bump", material.map_bump);
		trace("map_Po", material.map_Po);
		trace("Ns", material.Ns);
		trace("Tf", material.Tf);
		trace("Tr", material.Tr);
		trace("sharpness", material.sharpness);
		trace("d", material.d);
		trace("disp", material.disp);
		trace("decal", material.decal);
		trace("bump", material.bump);
		trace("illum", material.illum);
		trace("Ni", material.Ni);
		trace("refl", material.refl);
		trace("Pr", material.Pr);
		trace("Pm", material.Pm);
		trace("Ps", material.Ps);
		trace("Pc", material.Pc);
		trace("Pcr", material.Pcr);
		trace("aniso", material.aniso);
		trace("anisor", material.anisor);
		trace("norm", material.norm);
		trace("map_RMA", material.map_RMA);
		trace("map_ORM", material.map_ORM);
	}

	inline void trace(Load& load)
	{
		for( const auto& info : load.information() )
			std::cout << " " << info << std::endl;

		for( const auto& material : load.materials() )
			trace(material);

		std::cout << std::endl;
	}
}
