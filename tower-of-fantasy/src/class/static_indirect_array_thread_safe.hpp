#pragma once
#include "fwddec.hpp"

namespace big
{
#pragma pack(push, 1)
	template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
	class TStaticIndirectArrayThreadSafeRead
	{
	public:
		inline size_t Num() const
		{
			return NumElements;
		}
		inline bool IsValidIndex(int32_t index) const
		{
			return index < Num() && index >= 0;
		}
		inline ElementType const* const& operator[](int32_t index) const
		{
			return *GetItemPtr(index);
		}
	private:
		inline ElementType const* const* GetItemPtr(int32_t Index) const
		{
			int32_t ChunkIndex = Index / ElementsPerChunk;
			int32_t WithinChunkIndex = Index % ElementsPerChunk;
			ElementType** Chunk = Chunks[ChunkIndex];
			return Chunk + WithinChunkIndex;
		}
		enum
		{
			ChunkTableSize = (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk
		};
		ElementType** Chunks[ChunkTableSize];
		int32_t NumElements;
		int32_t NumChunks;
	};
#pragma pack(pop)
}