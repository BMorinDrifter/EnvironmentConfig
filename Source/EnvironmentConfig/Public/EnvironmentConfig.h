#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FEnvironmentConfigModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static FEnvironmentConfigModule* Get()
	{
		static FName environmentConfig(TEXT("EnvironmentConfig"));
		return &FModuleManager::LoadModuleChecked< FEnvironmentConfigModule >(environmentConfig);
	}

	const FString& GetEnvironmentName() { return EnvironmentName; }

protected:
	FString EnvironmentName;
};
