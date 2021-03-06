// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tracks/MovieSceneVectorTrack.h"
#include "Sections/MovieSceneVectorSection.h"


UMovieSceneVectorTrack::UMovieSceneVectorTrack( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	NumChannelsUsed = 0;
	SupportedBlendTypes = FMovieSceneBlendTypeField::All();
}


bool UMovieSceneVectorTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneVectorSection::StaticClass();
}

UMovieSceneSection* UMovieSceneVectorTrack::CreateNewSection()
{
	UMovieSceneVectorSection* NewSection = NewObject<UMovieSceneVectorSection>(this, NAME_None, RF_Transactional);
	NewSection->SetChannelsUsed(NumChannelsUsed);
	return NewSection;
}
