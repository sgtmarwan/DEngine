#pragma once
namespace DEngine
{
	class Shader
	{
	protected:

	public:
		virtual void Bind() const = 0;
		virtual ~Shader() = default;
	};

	class ShaderData
	{
	public:
		virtual void VSSet(const unsigned int slot) const = 0;
		virtual void PSSet(const unsigned int slot) const = 0;
		virtual ~ShaderData() = default;
	};
}

