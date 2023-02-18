#pragma once

/* Author: jrmwng @ 2023 */

// Reference: https://stackoverflow.com/questions/51538694/how-to-create-a-128-bit-integer-literal

namespace jrmwng
{
	namespace like2023
	{
		template <int nRADIX = 0, bool bNEGATE = false, bool bDEBUG = false>
		struct bigint_literal
		{
			static_assert(nRADIX <= 16, "Up to hexadecimal only");

			char const* const pcLiteral;

			template <typename Tint>
			constexpr operator Tint () const
			{
				Tint tInt(0);
				{
					for (char const* pcDigit = pcLiteral; *pcDigit; ++pcDigit)
					{
						char const cDigit = *pcDigit;

						Tint tMulti(1);
						Tint tDigit(0);

						if ('0' <= cDigit && cDigit < '0' + (nRADIX < 10 ? nRADIX : 10))
						{
							tMulti = Tint(nRADIX);
							tDigit = cDigit - '0';
						}
						else if (nRADIX <= 10)
						{
							if (bDEBUG)
							{
								throw pcLiteral;
							}
						}
						else
						{
							if ('A' <= cDigit && cDigit < 'A' + (nRADIX - 10))
							{
								tMulti = Tint(nRADIX);
								tDigit = 10 + (cDigit - 'A');
							}
							else if ('a' <= cDigit && cDigit < 'a' + (nRADIX - 10))
							{
								tMulti = Tint(nRADIX);
								tDigit = 10 + (cDigit - 'a');
							}
							else
							{
								if (bDEBUG)
								{
									throw pcLiteral;
								}
							}
						}

						if (bNEGATE)
						{
							tInt = tInt * tMulti - tDigit;
						}
						else
						{
							tInt = tInt * tMulti + tDigit;
						}
					}
				}
				return tInt;
			}

			constexpr bigint_literal<nRADIX, !bNEGATE, bDEBUG> operator- () const
			{
				return{ pcLiteral };
			}
		};
		template <bool bNEGATE, bool bDEBUG>
		struct bigint_literal<0, bNEGATE, bDEBUG>
		{
			template <int nRADIX>
			using Tbigint_literal = bigint_literal<nRADIX, bNEGATE, bDEBUG>;

			char const* const pcLiteral;

			template <typename Tint>
			constexpr operator Tint () const
			{
				char const* pcDigit = pcLiteral;

				if (pcDigit[0] == '0')
				{
					switch (pcDigit[1])
					{
					case 'x':
					case 'X':
						return Tbigint_literal<16>{pcDigit + 2};
					case 'b':
					case 'B':
						return Tbigint_literal<2>{pcDigit + 2};
					default:
						return Tbigint_literal<8>{pcDigit + 1};
					}
				}
				return Tbigint_literal<10>{pcDigit};
			}

			constexpr bigint_literal<0, !bNEGATE, bDEBUG> operator- () const
			{
				return{ pcLiteral };
			}
		};
	};
}
constexpr jrmwng::like2023::bigint_literal<0, false, false> operator"" _bigint(char const* pcLiteral)
{
	return{ pcLiteral };
}
constexpr jrmwng::like2023::bigint_literal<0, false, true> operator"" _dbgint(char const* pcLiteral)
{
	return{ pcLiteral };
}
