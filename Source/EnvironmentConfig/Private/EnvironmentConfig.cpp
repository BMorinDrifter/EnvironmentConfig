#include "EnvironmentConfig.h"
#include "Misc/ConfigCacheIni.h"

#define LOCTEXT_NAMESPACE "FEnvironmentConfigModule"

void FEnvironmentConfigModule::StartupModule()
{
	// Environment is specified on the command line so build artifacts can be re-used
	if (!FParse::Value(FCommandLine::Get(), TEXT("Env="), EnvironmentName))
	{
		if (IsRunningDedicatedServer() && !FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAME_ENVIRONMENT")).IsEmpty())
		{
			// Dedicated servers may also put it in an environment variable so containers can be re-used
			EnvironmentName = FGenericPlatformMisc::GetEnvironmentVariable(TEXT("GAME_ENVIRONMENT"));
		}
		else
		{
			// Everyone else defaults to Integration
			EnvironmentName = TEXT("Integration");
		}
	}

	// Epic usese magic epicsandboxid values, subsitute your own values
	FString epicEnvironment;
	if (FParse::Value(FCommandLine::Get(), TEXT("epicsandboxid="), epicEnvironment))
	{
		epicEnvironment.ToLowerInline();
		if (epicEnvironment == TEXT("p-qeej9b9vpdq2kc96zpmpzez5gcqyk8"))
		{
			EnvironmentName = TEXT("Integration");
		}
		else if (epicEnvironment == TEXT("p-azsygyjgqfn8ckh58c2bcg6zrq54y4"))
		{
			EnvironmentName = TEXT("PTR");
		}
		else if (epicEnvironment == TEXT("89018fd416314b829bbf175c0b4aa440"))
		{
			EnvironmentName = TEXT("Prod");
		}
	}

	UE_LOG(LogConfig, Log, TEXT("Loading EnvironmentConfig for %s"), *EnvironmentName);

	FString environmentDirectory = FPaths::ProjectConfigDir() / TEXT("Environment") / EnvironmentName;

	FConfigFile* config = GConfig->FindConfigFile(GGameIni);
	config->Combine(environmentDirectory / TEXT("Common.ini"));

	if (IsRunningDedicatedServer())
	{
		config->Combine(environmentDirectory / TEXT("Server.ini"));
	}
	else
	{
		config->Combine(environmentDirectory / TEXT("Client.ini"));
	}

#if WITH_EDITOR
	// Load both client and server config with server taking precedence
	config->Combine(environmentDirectory / TEXT("Server.ini"));
#endif
}

void FEnvironmentConfigModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEnvironmentConfigModule, EnvironmentConfig)