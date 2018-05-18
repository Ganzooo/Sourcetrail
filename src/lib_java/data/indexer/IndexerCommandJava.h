#ifndef INDEXER_COMMAND_JAVA_H
#define INDEXER_COMMAND_JAVA_H

#include <vector>

#include "data/indexer/IndexerCommand.h"

class FilePath;
class FilePathFilter;

class IndexerCommandJava
	: public IndexerCommand
{
public:
	static IndexerCommandType getStaticIndexerCommandType();

	IndexerCommandJava(
		const FilePath& sourceFilePath,
		const std::string& languageStandard,
		const std::vector<FilePath>& classPath);

	virtual IndexerCommandType getIndexerCommandType() const override;
	virtual size_t getByteSize(size_t stringSize) const override;

	std::string getLanguageStandard() const;

	void setClassPath(std::vector<FilePath> classPath);
	std::vector<FilePath> getClassPath() const;

private:
	const std::string m_languageStandard;
	std::vector<FilePath> m_classPath;
};

#endif // INDEXER_COMMAND_JAVA_H
