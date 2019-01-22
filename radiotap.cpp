#include "radiotap.h"
#include <bitset>


radiotap::radiotap(const u_char *data)
{
    header.revision = ((radiotap_header*) data)->revision;
    header.padding = ((radiotap_header*) data)->padding;
    header.length = ((radiotap_header*) data)->length;


    //present
    const u_char *data_present= data;
    while(((radiotap_present *)(data_present+4))->ext ){
        header.present_length ++;
        data_present += 4;
    }
    header.present = new radiotap_present[header.length];
    std::memcpy(header.present, data+4,sizeof(radiotap_present)*header.length);
    data += 4 +sizeof(radiotap_present)*header.present_length;


    int index=0;
    uint32_t present;
    std:memcpy(&present,header.present,sizeof(uint32_t));
    std::bitset<32> present_bits(present);
    for(int i=0;i<present_bits.size();i++){
        if(present_bits.test(i)){
            if(i==TSFT){
                tsft b;
                memcpy(&b,data,sizeof(tsft));
                elements[i]=b;
                data += sizeof(tsft);
            }
            else if(i==FLAGS){
                flags b;
                memcpy(&b,data,sizeof(flags));
                elements[i]=b;
                data += sizeof(flags);
            }
            else if(i==RATE){
                rate b;
                memcpy(&b,data,sizeof(rate));
                elements[i]=b;
                data += sizeof(rate);
            }
            else if(i==CHANNEL){
                channel b;
                memcpy(&b,data,sizeof(channel));
                elements[i]=b;
                data += sizeof(channel);
            }
            else if(i==FHSS){
                fhss b;
                memcpy(&b,data,sizeof(fhss));
                elements[i]=b;
                data += sizeof(fhss);
            }
            else if(i==ANTENNA_SIGNAL){
                antenna_signal b;
                memcpy(&b,data,sizeof(antenna_signal));
                elements[i]=b;
                data += sizeof(antenna_signal);
            }
            else if(i==ANTENNA_NOISE){
                antenna_noise b;
                memcpy(&b,data,sizeof(antenna_noise));
                elements[i]=b;
                data += sizeof(antenna_noise);
            }
            else if(i==LOCK_QUALITY){
                lock_quality b;
                memcpy(&b,data,sizeof(lock_quality));
                elements[i]=b;
                data += sizeof(lock_quality);
            }
            else if(i==TX_ATTENUATION){
                tx_attenuation b;
                memcpy(&b,data,sizeof(tx_attenuation));
                elements[i]=b;
                data += sizeof(tx_attenuation);
            }
            else if(i==DB_TX_ATTENUATION){
                db_tx_attenuation b;
                memcpy(&b,data,sizeof(db_tx_attenuation));
                elements[i]=b;
                data += sizeof(db_tx_attenuation);
            }
            else if(i==DBM_TX_POWER){
                dbm_tx_power b;
                memcpy(&b,data,sizeof(dbm_tx_power));
                elements[i]=b;
                data += sizeof(dbm_tx_power);
            }
            else if(i==ANTENNA){
                antenna b;
                memcpy(&b,data,sizeof(antenna));
                elements[i]=b;
                data += sizeof(antenna);
            }
            else if(i==DB_ANTENNA_SIGNAL){
                db_antenna_signal b;
                memcpy(&b,data,sizeof(db_antenna_signal));
                elements[i]=b;
                data += sizeof(db_antenna_signal);
            }
            else if(i==DB_ANTENNA_NOISE){
                db_antenna_noise b;
                memcpy(&b,data,sizeof(db_antenna_noise));
                elements[i]=b;
                data += sizeof(db_antenna_noise);
            }
            else if(i==RX_FLAGS){
                rx_flags b;
                memcpy(&b,data,sizeof(rx_flags));
                elements[i]=b;
                data += sizeof(rx_flags);
            }
            else if(i==TX_FLAGS){
                tx_flags b;
                memcpy(&b,data,sizeof(tx_flags));
                elements[i]=b;
                data += sizeof(tx_flags);
            }
            else if(i==HARDWARE_QUEUE){
                hardware_queue b;
                memcpy(&b,data,sizeof(hardware_queue));
                elements[i]=b;
                data += sizeof(hardware_queue);
            }
            else if(i==RSSI){
                rssi b;
                memcpy(&b,data,sizeof(rssi));
                elements[i]=b;
                data += sizeof(rssi);
            }
            else if(i==RTS_RETRIES){
                rts_retries b;
                memcpy(&b,data,sizeof(rts_retries));
                elements[i]=b;
                data += sizeof(rts_retries);
            }
            else if(i==DATA_RETRIES){
                data_retries b;
                memcpy(&b,data,sizeof(data_retries));
                elements[i]=b;
                data += sizeof(data_retries);
            }
            else if(i==XCHANNEL){
                xchannel b;
                memcpy(&b,data,sizeof(xchannel));
                elements[i]=b;
                data += sizeof(xchannel);
            }
            else if(i==MCS){
                mcs b;
                memcpy(&b,data,sizeof(mcs));
                elements[i]=b;
                data += sizeof(mcs);
            }
            else if(i==A_MPDU_STATUS){
                a_mpdu_status b;
                memcpy(&b,data,sizeof(a_mpdu_status));
                elements[i]=b;
                data += sizeof(a_mpdu_status);
            }
            else if(i==VHT){
                vht b;
                memcpy(&b,data,sizeof(vht));
                elements[i]=b;
                data += sizeof(vht);
            }
            else if(i==TIMESTAMP){
                timestamp b;
                memcpy(&b,data,sizeof(timestamp));
                elements[i]=b;
                data += sizeof(timestamp);
            }
            else if(i==EXTENDED_FLAGS){
                extended_flags b;
                memcpy(&b,data,sizeof(extended_flags));
                elements[i]=b;
                data += sizeof(extended_flags);
            }
            else if(i==HE){
                he b;
                memcpy(&b,data,sizeof(he));
                elements[i]=b;
                data += sizeof(he);
            }
            else if(i==HE_MU){
                he_mu b;
                memcpy(&b,data,sizeof(he_mu));
                elements[i]=b;
                data += sizeof(he_mu);
            }
            else if(i==HE_MU_OTHER_USER){
                he_mu_other_user b;
                memcpy(&b,data,sizeof(he_mu_other_user));
                elements[i]=b;
                data += sizeof(he_mu_other_user);
            }
            else if(i==ZERO_LENGTH_PSDU){
                zero_length_psdu b;
                memcpy(&b,data,sizeof(zero_length_psdu));
                elements[i]=b;
                data += sizeof(zero_length_psdu);
            }
            else if(i==L_SIG){
                l_sig b;
                memcpy(&b,data,sizeof(l_sig));
                elements[i]=b;
                data += sizeof(l_sig);
            }
            else if(i==RADIOTAP_NAMESPACE){
                radiotap_namespace b;
                memcpy(&b,data,sizeof(radiotap_namespace));
                elements[i]=b;
                data += sizeof(radiotap_namespace);
            }
            else if(i==VENDOR_NAMESPACE){
                vendor_namespace b;
                memcpy(&b,data,sizeof(vendor_namespace));
                elements[i]=b;
                data += sizeof(vendor_namespace);
            }
        }
    }
}
