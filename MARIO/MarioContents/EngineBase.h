#pragma once
#include <string>
#include <string_view>

// 설명 : 문자열 관련 처리 클래스
class UEngineString
{
public:
	/// <summary>
	/// 대문자로 변환하는 함수
	/// </summary>
	/// <param name="_View">변환할 문자열</param>
	/// <returns></returns>
	static std::string ToUpper(std::string_view _View);

	/// <summary>
	/// 멀티 바이트 문자열을 와이드 바이트 문자열로 변환하는 함수
	/// </summary>
	/// <param name="_View">변환할 문자열</param>
	/// <returns></returns>
	static std::wstring AnsiToUniCode(std::string_view _View);

protected:

private:
	// constrcuter destructer
	UEngineString();
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;
};

