/*
  WavefrontMTL.h
    
  Wavefront MTL Parser - C++ Class for Parsing Material Information
  
  A header-only C++ code solution for parsing Wavefront MTL files, with no
  external dependencies other than the Standard Template Library (STL).
  The code provides comprehensive support for reading and parsing all known
  material parameters, including standard MTL parameters as well as additional
  parameters used in Clara.io and DirectXMesh. Runs for C++ 17. If you need
  to run this for C++ 11, move line 190 to a cpp in your project.
  
  It allows for easy extraction of header information and materials,
  enabling access to material properties such as ambient color, diffuse color,
  specular color, transparency, shininess, metalness, roughness, etc.
  
  The solution is self-contained in a single header file, making it easy to
  integrate into existing projects without the need for additional libraries
  or dependencies.
  
  Key Features:
  
  - Supports parsing of standard MTL parameters
  - Supports parsing of Clara.io MTL parameters
  - Supports parsing of DirectXMesh MTL parameters
  - Retrieves header information and all materials in the MTL file
  - Provides convenient access to material properties
  - Robust and efficient parsing algorithm for handling large MTL files
  - Suitable for integration into 3D graphics applications, game engines,
    and other computer graphics projects
  
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

#include <string>
#include <vector>

namespace mtl
{
	struct Material;

	class Load
	{
	public:

		explicit Load();

		explicit Load(const Material& material);

		~Load();

		Load(const Load&) = delete;

		Load(const Load&&) = delete;

		Load& operator=(const Load&) = delete;

		Load& operator=(const Load&&) = delete;

		bool load(const std::string& path);

		std::vector<Material>& materials()
		{
			return mtl;
		}

		bool lookup(const std::string& materialName, Material& material) const;

		std::vector<std::string>& information()
		{
			return info;
		}

		void trace();

	private:

		Material default_material() const;

		bool open(const std::string& open_path);

		bool close();

		bool error();

		FILE* file;

		std::string path; // Material file 	

		std::vector<Material> mtl; // List of all materials found in file

		std::vector<std::string> info; // List of all comment lines in the header of file
	};

	struct Parse
	{
		friend class Load;

		Parse() : parse(false) { }

		Parse& operator=(const Parse& copy)
		{
			parse = active ? copy.parse : false;

			return *this;
		}

		bool parsed(bool set = true)
		{
			parse = set;

			return parse;
		}

		bool isParsed() const { return parse; }

	private:

		bool parse;

	protected:

		static bool active;
	};

	inline bool Parse::active = true; //This declaration is legal for C++ 17 (move this to a cpp if C++ 11)

	template <typename T>
	struct Value : Parse
	{
		Value() : Parse(), value(T()) {}

		Value(const T& value) : value(std::move(value)) {}

		Value& operator=(const T& copy)
		{
			parsed();

			value = copy;

			return *this;
		}

		operator T() { return value; }

		operator const T&() const { return value; }

		T value;
	};

	struct uvw : Parse
	{
		uvw() : Parse(), u(0), v(0), w(0) { }

		uvw(const double& u, const double& v, const double& w) : Parse(), u(u), v(v), w(w) { }

		double u; // Texture coordinate u mapping [0..1]
		double v; // Texture coordinate v mapping [0..1]
		double w; // Texture coordinate w mapping [0..1]
	};

	struct rgb : Parse
	{
		rgb() : Parse(), r(0), g(0), b(0) { }

		rgb(const double& r, const double& g, const double& b) : Parse(), r(r), g(g), b(b) { }

		double r; // Ambient color red   [0..1]
		double g; // Ambient color green [0..1]
		double b; // Ambient color blue  [0..1]
	};

	struct xyz : Parse
	{
		xyz() : Parse(), x(0), y(0), z(0) { }

		xyz(const double& x, const double& y, const double& z) : Parse(), x(x), y(y), z(z) { }

		double x; //  tristimulus x value in CIE
		double y; //  tristimulus y value in CIE
		double z; //  tristimulus z value in CIE
	};

	struct Model : Parse
	{
		Model() : Parse(), base(0), gain(1) { }

		Model(const int base, const int gain) : Parse(), base(base), gain(gain) {}

		int base; // Base color or albedo of a material [0..1]
		int gain; // Gain factor for the texture map
	};
	
	struct Opacity : Parse
	{
		Opacity() : Parse(), d(1), halo(false) {}

		Opacity(const double& d, const bool halo) : Parse(), d(d), halo(halo) {}

		double d;    // Transparency [0..1]
		bool   halo; // Halo effect (maximum intensity)
	};

	struct Spectral : Parse
	{
		Spectral() : Parse(), factor(1) {}

		Spectral(std::string& file, const double& factor) : Parse(), file(std::move(file)), factor(factor) {}

		std::string file;   // Spectral file
		double      factor; // Scaling factor
	};

	struct Color : Parse
	{
		Color() : Parse() {}

		rgb      color;       // Ambient color RGB
		xyz      color_space; // Ambient color in the CIE XYZ
		Spectral spectral;    // Color using a spectral file, Radiance RGBE
	};

	struct Texture : Parse
	{
		Texture() : Parse(), blendu(true), blendv(true), clamp(false), cc(false), boost(60), texres(1), imfchan('m') {}

		Value<std::string> file;

		Value<bool>   blendu;  // Horizontal texture blending
		Value<bool>   blendv;  // Vertical texture blending
		Value<bool>   clamp;   // Only render textures in clamped range
		Value<bool>   cc;      // Color correction
		Value<double> bm;      // Bump map multiplier
		Value<double> boost;   // Sharpness
		Value<double> texres;  // Texture resolution multiplie
		Model         mm;      // Modify texture values 	
		uvw           o;       // Moves texture origin
		uvw           s;       // Adjusts texture scale
		uvw           t;       // Controls texture turbulence
		Value<char>   imfchan; // Specifies witch channels to use for the file [r, g, b, m, l, z] 
	};

	struct Reflection : Parse
	{
		Reflection() : Parse() {}

		Texture sphere;      // Reflection texture map
		Texture cube_top;    // Reflection texture map
		Texture cube_bottom; // Reflection texture map
		Texture cube_front;  // Reflection texture map
		Texture cube_back;   // Reflection texture map
		Texture cube_left;   // Reflection texture map
		Texture cube_right;  // Reflection texture map
	};

	//-------------------------------------------------------------------------------------------------------

	struct Material
	{
		Material() : Ns(0), sharpness(60), illum(0), Ni(0), Tr(1), Pr(0), Pm(0), Ps(0), Pc(0), Pcr(0), aniso(0), anisor(0) {}

		Value<std::string> name;      // Material name
		Color              Kd;        // Color
		Color              Ka;        // Color Ambient
		Color              Ks;        // Color Specular
		Color              Tf;        // Color Transmission
		Value<double>      Ns;        // Shininess  factor [0..1000]
		Texture            map_Kd;    // Texture Diffuse
		Texture            map_Ka;    // Texture Ambient
		Texture            map_Ks;    // Texture Specular
		Texture            map_Ns;    // Texture Glossiness			(Specular highlight component)
		Texture            map_Pr;    // Texture Roughness
		Texture            map_Pm;    // Texture Metalness
		Texture            map_Ps;    // Texture Sheen
		Texture            map_d;     // Opacity Texture (alpha)
		Texture            map_bump;  // Normal texture
		Texture            map_Po;    // Texture Occlusion
		Value<double>      sharpness; // Sharpness value [0..1000]
		Opacity            d;         // Dissolve factor
		Texture            disp;      // Displacement map
		Texture            decal;     // Stencil decal
		Texture            bump;      // Normal texture, some use bump instead of map_bump
		Value<int>         illum;     // Illumination [0..10]
		Value<double>      Ni;        // Optical density
		Value<double>      Tr;        // Transparency
		Reflection         refl;      // Reflection map statements	(Sphere/Cube)
		Color              Ke;        // Color Emissive				(Physically Rendering/Clara.io)
		Value<double>      Pr;        // Roughness factor			(Physically Rendering/Clara.io)
		Value<double>      Pm;        // Metalness factor			(Physically Rendering/Clara.io)
		Value<double>      Ps;        // Sheen factor				(Physically Rendering/Clara.io)
		Value<double>      Pc;        // Thickness factor			(Physically Rendering/Clara.io)
		Value<double>      Pcr;       // Roughness factor			(Physically Rendering/Clara.io)
		Value<double>      aniso;     // Anisotropy					(Physically Rendering/Clara.io)
		Value<double>      anisor;    // Anisotropy rotation		(Physically Rendering/Clara.io)
		Texture            map_Ke;    // Texture Emissive			(Physically Rendering/Clara.io)
		Texture            norm;      // Texture Normal				(Physically Rendering/Clara.io)
		Texture            map_RMA;   // Texture RMA				(DirectXMesh/Microsoft's DirectX engine)
		Texture            map_ORM;   // Texture ORM				(DirectXMesh/Microsoft's DirectX engine)
	};

	//-------------------------------------------------------------------------------------------------------

	constexpr int BUFFER_CHAR = 1000;

	char* trim(char*);

	template <typename T>
	bool parse(char* line, Value<T>&);

	template <typename T>
	bool parse(char* line, Value<T>&, char*&);

	bool parse(char* line, Color&);

	bool parse(char* line, Opacity&);

	bool parse(char* line, Texture&);

	bool parse(char* line, Reflection&);

	bool char_cmp(const char*, const std::string&);
		
	//-------------------------------------------------------------------------------------------------------

	inline Load::Load() : file(nullptr) { }

	inline Load::Load(const Material& material) : Load()
	{
		mtl.emplace_back(material);
	}

	inline Load::~Load() { close(); }

	inline bool Load::open(const std::string& open_path)
	{
		close();

		path = open_path;

		const auto open = fopen_s(&file, path.c_str(), "rb");

		if( open == 0 ) return true;

		printf("Impossible to open the file !\n");

		return false;
	}

	inline bool Load::close()
	{
		if( !file ) return true;

		const auto res = fclose(file);

		file = nullptr;

		return res == 0 ? true : false;
	}

	inline bool Load::error()
	{
		close();

		return false;
	}

	inline bool Load::lookup(const std::string& materialName, Material& material) const
	{
		for( const auto& item : mtl )
		{
			if( materialName == item.name.value )
			{
				material = item;

				return true;
			}
		}

		return false;
	}
	
	inline Material Load::default_material() const
	{
		Material material;

		if( mtl.empty() ) return material;

		Parse::active = false;
		material      = mtl.front();
		Parse::active = true;

		return material;
	}

	inline bool Load::load(const std::string& path)
	{
		if( !open(path) ) return false;

		Material material = default_material();

		mtl.clear();

		info.clear();

		mtl.emplace_back(material);

		char buff[BUFFER_CHAR] = {0};

		std::string text;

		while( fgets(buff, sizeof buff, file) )
		{
			char* line = trim(buff);

			auto& m = mtl.back();

			if( *line == '#' )
			{
				if( !m.name.isParsed() )
					info.emplace_back(trim(line + 1));
			}
			else if( char_cmp(line, "newmtl") )
			{
				if( m.name.isParsed() )
					mtl.emplace_back(material);

				mtl.back().name = trim(line + 7);
			}
			else if( char_cmp(line, "Kd ") )
				parse(line + 3, m.Kd);
			else if( char_cmp(line, "Ka ") )
				parse(line + 3, m.Ka);
			else if( char_cmp(line, "Ks ") )
				parse(line + 3, m.Ks);
			else if( char_cmp(line, "Tf ") )
				parse(line + 3, m.Tf);
			else if( char_cmp(line, "Ns ") )
				parse(line + 3, m.Ns);
			else if( char_cmp(line, "map_Kd ") )
				parse(line + 7, m.map_Kd);
			else if( char_cmp(line, "map_Ka ") )
				parse(line + 7, m.map_Ka);
			else if( char_cmp(line, "map_Ks ") )
				parse(line + 7, m.map_Ks);
			else if( char_cmp(line, "map_Ns ") )
				parse(line + 7, m.map_Ns);
			else if( char_cmp(line, "map_Pr ") )
				parse(line + 7, m.map_Pr);
			else if( char_cmp(line, "map_Pm ") )
				parse(line + 7, m.map_Pm);
			else if( char_cmp(line, "map_Ps ") )
				parse(line + 7, m.map_Ps);
			else if( char_cmp(line, "map_d ") )
				parse(line + 6, m.map_d);
			else if( char_cmp(line, "map_bump ") )
				parse(line + 9, m.map_bump);
			else if( char_cmp(line, "map_Po ") )
				parse(line + 7, m.map_Po);
			else if( char_cmp(line, "sharpness ") )
				parse(line + 10, m.sharpness);
			else if( char_cmp(line, "d ") )
				parse(line + 2, m.d);
			else if( char_cmp(line, "disp ") )
				parse(line + 5, m.disp);
			else if( char_cmp(line, "decal ") )
				parse(line + 6, m.decal);
			else if( char_cmp(line, "bump ") )
				parse(line + 5, m.bump);
			else if( char_cmp(line, "illum ") )
				parse(line + 6, m.illum);
			else if( char_cmp(line, "Ni ") )
				parse(line + 3, m.Ni);
			else if( char_cmp(line, "Tr ") )
				parse(line + 3, m.Tr);
			else if( char_cmp(line, "refl ") )
				parse(line + 5, m.refl);
			else if( char_cmp(line, "Ke ") )
				parse(line + 3, m.Ke);
			else if( char_cmp(line, "Pr ") )
				parse(line + 3, m.Pr);
			else if( char_cmp(line, "Pm ") )
				parse(line + 3, m.Pm);
			else if( char_cmp(line, "Ps ") )
				parse(line + 3, m.Ps);
			else if( char_cmp(line, "Pc ") )
				parse(line + 3, m.Pc);
			else if( char_cmp(line, "Pcr ") )
				parse(line + 4, m.Pcr);
			else if( char_cmp(line, "aniso ") )
				parse(line + 6, m.aniso);
			else if( char_cmp(line, "anisor ") )
				parse(line + 7, m.anisor);
			else if( char_cmp(line, "map_Ke ") )
				parse(line + 7, m.map_Ke);
			else if( char_cmp(line, "norm ") )
				parse(line + 5, m.norm);
			else if( char_cmp(line, "map_RMA ") )
				parse(line + 8, m.map_RMA);
			else if( char_cmp(line, "map_ORM ") )
				parse(line + 8, m.map_ORM);
		}

		return mtl.front().name.isParsed();
	}

	//-------------------------------------------------------------------------------------------------------

	inline std::string strtoword(char* text, char*& end)
	{
		end = text;

		if( text == nullptr )
			return {};

		if( *text == '\0' )
			return {};

		while( std::isspace(*text) )
			text++;

		char* start = text;

		while( *text != '\0' )
		{
			if( std::isspace(*text) )
				break;

			text++;
		}

		if( start == text )
			return {};

		end = text;

		return {start , text};
	}

	//-------------------------------------------------------------------------------------------------------

	inline bool parse(char* line, std::string& s, char*& end)
	{
		if( line == nullptr ) return false;

		s = strtoword(line, end);

		return true;
	}

	inline bool parse(const char* line, int& i, char*& end)
	{
		if( line == nullptr ) return false;

		i = static_cast<int>(strtoll(line, &end, 10));

		return true;
	}

	inline bool parse(const char* line, double& d, char*& end)
	{
		if( line == nullptr ) return false;

		d = std::strtod(line, &end);

		return true;
	}

	inline bool parse(char* line, uvw& uvw, char*& end)
	{
		uvw.parsed(false);

		if( !parse(line, uvw.u, line) )
			return false;

		uvw.parsed(true);

		if( !parse(line, uvw.v, line) )
		{
			uvw.v = uvw.w = uvw.u;

			end = line;

			return true;
		}

		if( !parse(line, uvw.w, end) )
			uvw.w = uvw.u;

		return true;
	}

	inline bool parse(char* line, rgb& rgb, char*& end)
	{
		rgb.parsed(false);

		if( !parse(line, rgb.r, line) )
			return false;

		rgb.parsed(true);

		if( !parse(line, rgb.g, line) )
		{
			rgb.g = rgb.b = rgb.r;

			end = line;

			return true;
		}

		if( !parse(line, rgb.b, end) )
			rgb.b = rgb.r;

		return true;
	}

	inline bool parse(char* line, xyz& xyz, char*& end)
	{
		xyz.parsed(false);

		if( !parse(line, xyz.x, line) )
			return false;

		xyz.parsed(true);

		if( !parse(line, xyz.y, line) )
		{
			xyz.y = xyz.z = xyz.x;

			end = line;

			return true;
		}

		if( !parse(line, xyz.z, end) )
			xyz.z = xyz.x;

		return true;
	}

	inline bool parse(char* line, Model& mm, char*& end)
	{
		mm.parsed(false);

		if( !parse(line, mm.base, line) )
			return false;

		mm.parsed(true);

		if( !parse(line, mm.gain, end) )
			end = line;

		return true;
	}
		
	inline bool parse(char* line, Spectral& spectral, char*& end)
	{
		spectral.parsed(false);

		if( !parse(line, spectral.file, line) )
			return false;

		spectral.parsed(true);

		if( !parse(line, spectral.factor, end) )
			end = line;

		return true;
	}
	
	inline bool parse(char* line, Color& color, char*& end)
	{
		if( char_cmp(line, "spectral ") )
			return color.parsed(parse(line + 9, color.spectral, end));
		
		if( char_cmp(line, "xyz ") )
			return color.parsed(parse(line + 4, color.color_space, end));

		return color.parsed(parse(line, color.color, end));
	}

	inline bool parse(char* line, Color& color)
	{
		return parse(line, color, line);
	}
	
	inline bool parse(char* line, Opacity& opacity, char*& end)
	{
		opacity.parsed(false);

		auto* p = line;

		while( *p != '\0' )
		{
			if( *p == '-' )
			{
				p++;

				if( char_cmp(p, "halo ") && parse(p + 5, opacity.d, end) )
				{
					opacity.parsed(true);

					opacity.halo = true;

					return true;
				}
			}

			p++;
		}

		return opacity.parsed(parse(line, opacity.d, end));
	}

	inline bool parse(char* line, Opacity& opacity)
	{
		return parse(line, opacity, line);
	}

	inline bool parse(char* line, Texture& texture, char*& end)
	{
		auto* p = line;

		std::string temp;

		bool isParsed(false);

		while( *p != '\0' )
		{
			if( *p == '-' )
			{
				p++;

				temp.clear();

				if( char_cmp(p, "blendu ") && parse(p + 7, temp, end) )
				{
					if( temp == "on" )
						texture.blendu = true;

					if( temp == "off" )
						texture.blendu = false;

					if( temp == "on" || temp == "off" )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "blendv ") && parse(p + 7, temp, end) )
				{
					if( temp == "on" )
						texture.blendv = true;

					if( temp == "off" )
						texture.blendv = false;

					if( temp == "on" || temp == "off" )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "clamp ") && parse(p + 6, temp, end) )
				{
					if( temp == "on" )
						texture.clamp = true;

					if( temp == "off" )
						texture.clamp = false;

					if( temp == "on" || temp == "off" )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "boost ") )
				{
					if( parse(p + 6, texture.boost, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "mm ") )
				{
					if( parse(p + 3, texture.mm, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "o ") )
				{
					if( parse(p + 2, texture.o, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "s ") )
				{
					if( parse(p + 2, texture.s, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "t ") )
				{
					if( parse(p + 2, texture.t, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "bm ") )
				{
					if( parse(p + 3, texture.bm, end) )
						isParsed = true;

					p = end;

					continue;
				}

				if( char_cmp(p, "imfchan ") )
				{
					if( parse(p + 8, temp, end) && !temp.empty() )
					{
						if( temp.find_first_of("rgbmlz") != std::string::npos )
						{
							texture.imfchan = *temp.c_str();

							isParsed = true;
						}

						p = end;

						continue;
					}
				}
			}

			p++;
		}

		p = end ? trim(end) : trim(line);

		if( p && *p && *p != '\0' )
		{
			isParsed = true;

			texture.file = p;
			texture.file.parsed();
		}

		return texture.parsed(isParsed);
	}

	inline bool parse(char* line, Texture& texture)
	{
		return parse(line, texture, line);
	}

	inline bool parse(char* line, Reflection& reflection)
	{
		reflection.parsed(false);

		auto* p = line;

		std::string temp;

		while( *p != '\0' )
		{
			if( *p == '-' )
			{
				p++;

				if( char_cmp(p, "type ") && parse(p + 5, temp, p) )
				{
					if( char_cmp(temp.c_str(), "sphere") )
						return reflection.parsed(parse(p, reflection.sphere, p));

					if( char_cmp(temp.c_str(), "cube_top") )
						return reflection.parsed(parse(p, reflection.cube_top, p));

					if( char_cmp(temp.c_str(), "cube_bottom") )
						return reflection.parsed(parse(p, reflection.cube_bottom, p));

					if( char_cmp(temp.c_str(), "cube_front") )
						return reflection.parsed(parse(p, reflection.cube_front, p));

					if( char_cmp(temp.c_str(), "cube_back") )
						return reflection.parsed(parse(p, reflection.cube_back, p));

					if( char_cmp(temp.c_str(), "cube_left") )
						return reflection.parsed(parse(p, reflection.cube_left, p));

					if( char_cmp(temp.c_str(), "cube_right") )
						return reflection.parsed(parse(p, reflection.cube_right, p));

					return false;
				}
			}

			p++;
		}

		return false;
	}

	//-------------------------------------------------------------------------------------------------------

	template <typename T>
	bool parse(char* line, Value<T>& t, char*& end)
	{
		T temp;

		t.parsed(false);

		if( !parse(line, temp, end) )
			return false;

		t = temp;

		return t.parsed(true);
	}

	template <typename T>
	bool parse(char* line, Value<T>& t)
	{
		return parse(line, t, line);
	}
	
	//-------------------------------------------------------------------------------------------------------

	inline bool char_cmp(const char* a, const char* b, const size_t length)
	{
		if( length == 0 ) return false;
		if( a == nullptr ) return false;
		if( b == nullptr ) return false;

		size_t n(0);

		while( a && *a && *a != '\0' && n < length )
		{
			n++;

			if( b && *b && *b != '\0' )
			{
				if( *a != *b )
					return false;
			}
			else
				return false;

			a++;
			b++;
		}

		return n == length;
	}

	inline bool char_cmp(const char* a, const std::string& b)
	{
		return char_cmp(a, b.c_str(), b.length());
	}

	inline char* trim(char* p)
	{
		if( p == nullptr ) return nullptr;

		while( std::isspace(*p) && *p != '\0' ) p++;

		const char* s = p;

		char* e = p;

		while( *e != '\0' ) e++;

		if( e != s ) e--;

		while( std::isspace(*e) && e != s ) e--;

		if( e != s ) e++;

		*e = '\0';

		return p;
	}
}
