// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "pch.h"
#include "AppConfiguration_WinRT.h"

#if UWP_API || UNIT_TEST_SERVICES
#include "SignInUISettings_WinRT.h"
#endif

using namespace Concurrency;
using namespace Platform;
using namespace std;

NAMESPACE_MICROSOFT_XBOX_SERVICES_BEGIN

XboxLiveAppConfiguration^ XboxLiveAppConfiguration::SingletonInstance::get()
{
    return ref new XboxLiveAppConfiguration(xbox::services::xbox_live_app_config::get_app_config_singleton());
}

XboxLiveAppConfiguration::XboxLiveAppConfiguration(
    _In_ std::shared_ptr<xbox::services::xbox_live_app_config> cppObj
    ) :
    m_cppObj(std::move(cppObj))
{
}

#if UWP_API || UNIT_TEST_SERVICES
SignInUISettings^
XboxLiveAppConfiguration::AppSignInUISettings::get()
{
	return ref new SignInUISettings(m_cppObj);
}
#endif

NAMESPACE_MICROSOFT_XBOX_SERVICES_END
