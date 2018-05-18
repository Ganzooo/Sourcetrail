#include "settings/SourceGroupSettings.h"

#include "settings/ProjectSettings.h"
#include "utility/ConfigManager.h"

const size_t SourceGroupSettings::s_version = 1;
const std::string SourceGroupSettings::s_keyPrefix = "source_groups/source_group_";

SourceGroupSettings::SourceGroupSettings(
	const std::string& id, SourceGroupType type, const ProjectSettings* projectSettings
)
	: m_projectSettings(projectSettings)
	, m_id(id)
	, m_name(sourceGroupTypeToString(type))
	, m_type(type)
	, m_status(SOURCE_GROUP_STATUS_ENABLED)
	, m_standard("")
{
}

void SourceGroupSettings::load(std::shared_ptr<const ConfigManager> config)
{
	const std::string key = s_keyPrefix + getId();

	const std::string name = config->getValueOrDefault<std::string>(key + "/name", "");
	if (!name.empty())
	{
		setName(name);
	}

	setStatus(stringToSourceGroupStatusType(config->getValueOrDefault(key + "/status", sourceGroupStatusTypeToString(SOURCE_GROUP_STATUS_ENABLED))));
	setStandard(config->getValueOrDefault<std::string>(key + "/standard", ""));
}

void SourceGroupSettings::save(std::shared_ptr<ConfigManager> config)
{
	const std::string key = s_keyPrefix + getId();

	config->setValue(key + "/status", sourceGroupStatusTypeToString(getStatus()));
	config->setValue(key + "/name", getName());
	config->setValue(key + "/standard", getStandard());
}

bool SourceGroupSettings::equals(std::shared_ptr<SourceGroupSettings> other) const
{
	return (
		m_id == other->m_id &&
		m_name == other->m_name &&
		m_type == other->m_type &&
		m_status == other->m_status &&
		m_standard == other->m_standard
	);
}

std::string SourceGroupSettings::getId() const
{
	return m_id;
}

void SourceGroupSettings::setId(const std::string& id)
{
	m_id = id;
}

SourceGroupType SourceGroupSettings::getType() const
{
	return m_type;
}

LanguageType SourceGroupSettings::getLanguage() const
{
	return getLanguageTypeForSourceGroupType(getType());
}

std::string SourceGroupSettings::getName() const
{
	return m_name;
}

void SourceGroupSettings::setName(const std::string& name)
{
	m_name = name;
}

SourceGroupStatusType SourceGroupSettings::getStatus() const
{
	return m_status;
}

void SourceGroupSettings::setStatus(SourceGroupStatusType status)
{
	m_status = status;
}

FilePath SourceGroupSettings::getProjectDirectoryPath() const
{
	return m_projectSettings->getProjectDirectoryPath();
}

FilePath SourceGroupSettings::makePathExpandedAndAbsolute(const FilePath& path) const
{
	return m_projectSettings->makePathExpandedAndAbsolute(path);
}

std::vector<FilePath> SourceGroupSettings::makePathsExpandedAndAbsolute(const std::vector<FilePath>& paths) const
{
	return m_projectSettings->makePathsExpandedAndAbsolute(paths);
}

std::string SourceGroupSettings::getStandard() const
{
	if (m_standard.empty())
	{
		return getDefaultStandard();
	}
	return m_standard;
}

void SourceGroupSettings::setStandard(const std::string& standard)
{
	m_standard = standard;
}
