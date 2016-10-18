// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file AESGCMGMAC_KeyExchange.cpp
 */

#include <sstream>
#include "AESGCMGMAC_KeyExchange.h"

using namespace eprosima::fastrtps::rtps::security;

AESGCMGMAC_KeyExchange::AESGCMGMAC_KeyExchange(){}
AESGCMGMAC_KeyExchange::~AESGCMGMAC_KeyExchange(){}

bool AESGCMGMAC_KeyExchange::create_local_participant_crypto_tokens(
            ParticipantCryptoTokenSeq &local_participant_crypto_tokens,
            const ParticipantCryptoHandle &local_participant_crypto,
            const ParticipantCryptoHandle &remote_participant_crypto,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}
     
bool AESGCMGMAC_KeyExchange::set_remote_participant_crypto_tokens(
            const ParticipantCryptoHandle &local_participant_crypto,
            const ParticipantCryptoHandle &remote_participant_crypto,
            const ParticipantCryptoTokenSeq &remote_participant_tokens,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}

bool AESGCMGMAC_KeyExchange::create_local_datawriter_crypto_tokens(
            DatawriterCryptoTokenSeq &local_datawriter_crypto_tokens,
            const DatawriterCryptoHandle &local_datawriter_crypto,
            const DatareaderCryptoHandle &remote_datareader_crypto,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}

bool AESGCMGMAC_KeyExchange::create_local_datareader_crypto_tokens(
            DatareaderCryptoTokenSeq &local_datareader_crypto_tokens,
            const DatareaderCryptoHandle &local_datareader_crypto,
            const DatawriterCryptoHandle &remote_datawriter_crypto,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}

bool AESGCMGMAC_KeyExchange::set_remote_datareader_crypto_tokens(
            const DatawriterCryptoHandle &local_datawriter_crypto,
            const DatareaderCryptoHandle &remote_datareader_crypto,
            const DatareaderCryptoTokenSeq &remote_datareader_tokens,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}

bool AESGCMGMAC_KeyExchange::return_crypto_tokens(
            const CryptoTokenSeq &crypto_tokens,
            SecurityException &exception){

    exception = SecurityException("Not implemented"); 
    return false;
}

std::string AESGCMGMAC_KeyExchange::KeyMaterialCDRSerialize(KeyMaterial_AES_GCM_GMAC &key){

std::stringstream buffer;
    
    buffer << "4";
    for(int i=0;i<4;i++){
        buffer << key.transformation_kind[i];
    }
    buffer << "32";
    for(int i=0;i<32;i++){
        buffer << key.master_salt[i];
    }
    buffer << "4";
    for(int i=0;i<4;i++){
        buffer << key.sender_key_id[i];
    }
    buffer << "32";
    for(int i=0;i<32;i++){
        buffer << key.master_sender_key[i];
    }
    buffer << "4";
    for(int i=0;i<4;i++){
        buffer << key.receiver_specific_key_id[i];
    }
    buffer << "32";
    for(int i=0;i<32;i++){
        buffer << key.master_receiver_specific_key[i];
    }

    return buffer.str();
}

KeyMaterial_AES_GCM_GMAC AESGCMGMAC_KeyExchange::KeyMaterialCDRDeserialize(std::string &CDR){
unsigned short index = 0;
KeyMaterial_AES_GCM_GMAC buffer;
    for(int i=1; i<5; i++){
        buffer.transformation_kind[i-1] = CDR.at(i);
    }
    for(int i=6; i<38; i++){
        buffer.master_salt[i-6] = CDR.at(i);
    }
    for(int i=39; i<43; i++){
        buffer.sender_key_id[i-39] = CDR.at(i);
    }
    for(int i=44; i<76; i++){
        buffer.master_sender_key[i-44] = CDR.at(i);
    }
    for(int i=77; i<81; i++){
        buffer.receiver_specific_key_id[i-77] = CDR.at(i);
    }
    for(int i=82; i< 114; i++){
        buffer.master_receiver_specific_key[i-82] = CDR.at(i);
    }
    return buffer;
}

