#include "Globals.h"

void InitGlobals()
{
	InitSingletons();
}

void InitSingletons()
{
	std::shared_ptr<Tag2D::LoggerOptions> options = std::make_shared<Tag2D::LoggerOptions>();
	options->info_prefix = "!w[INFO]!d ";
	options->warning_prefix = "!y[WARNING]!d ";
	options->error_prefix = "!r[ERROR]!d ";

	Tag2D::Logger::Instance().Init(options);
}