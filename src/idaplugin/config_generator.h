/**
 * @file idaplugin/config_generator.h
 * @brief Module contains classes/methods dealing with information export
 *        from IDA Pro to Retargetable Decompiler config database.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#ifndef IDAPLUGIN_CONFIG_GENERATOR_H
#define IDAPLUGIN_CONFIG_GENERATOR_H

#include <map>

#include "defs.h"

namespace idaplugin {

/**
 * Read information from IDA SDK structures and store it into
 * retargetable decompiler's configuration database.
 */
class ConfigGenerator
{
	public:
		ConfigGenerator(RdGlobalInfo &gi);
		std::string generate();

	private:
		void generateHeader();
		void generateFunctions();
		void generateFunctionType(const tinfo_t &fncType, retdec_config::Function &ccFnc);
		void generateSegmentsAndGlobals();
		retdec_config::Storage generateObjectLocation(const argloc_t &loc, const tinfo_t &locType);
		void generateCallingConvention(const cm_t &idaCC, retdec_config::CallingConvention &configCC);

		std::string addrType2string(ea_t addr);
		std::string type2string(const tinfo_t &type);
		std::string defaultTypeString();

	private:
		void dumpAllRegisters();

	private:
		RdGlobalInfo &decompInfo;
		retdec_config::Config &config; ///< Configuration object.
		std::map<tinfo_t,std::string> structIdSet; ///< Global variables.
};

} // namespace idaplugin

#endif
