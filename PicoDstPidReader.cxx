#define PicoDstPidReader_cxx
#include "PicoDstPidReader.h"

void PicoDstPidReader::Loop()
{   
   if (fChain == 0) return;
   
   bins->SetPtBins(ptBins,NptBins);
   bins->SetRapidityBins(rapidityBins,NrapidityBins);
   bins->SetEtaBins(etaBins,NetaBins);
   
   int ptBin, etaBin, rapidityBin;
   
   InitAllHisto();
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if (jentry % 1000 == 0) std::cout << "Entry : " << jentry << std::endl;
      
      for (Long64_t iTrack=0; iTrack<n_tracks_mpd; iTrack++){
         ptBin    = bins->GetPtBin( TMath::Abs(signed_pt_mpd[iTrack]) );
         etaBin   = bins->GetEtaBin( eta_mpd[iTrack] );
         
         if (ptBin < 0 || ptBin > bins->GetPtBinSize() || etaBin < 0 || etaBin > bins->GetEtaBinSize() ) continue;
         
         h_mass2[0][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
         if (PDG_code_mc[id_from_mc_mpd[iTrack]] == -211 || PDG_code_mc[id_from_mc_mpd[iTrack]] == 211 || PDG_code_mc[id_from_mc_mpd[iTrack]] == -321 || PDG_code_mc[id_from_mc_mpd[iTrack]] == 321 || PDG_code_mc[id_from_mc_mpd[iTrack]] == -2212 || PDG_code_mc[id_from_mc_mpd[iTrack]] == 2212)
            h_PDG_mass2[0][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
         else{
            h_bad_PDG[0][ptBin][etaBin]->Fill(PDG_code_mc[id_from_mc_mpd[iTrack]]);
            //if (PDG_code_mc[id_from_mc_mpd[iTrack]] > 1e6) std::cout << PDG_code_mc[id_from_mc_mpd[iTrack]] << std::endl;
         }
         
         if (pid_tpc_prob_pion_mpd[iTrack] > 0.9 && pid_tpc_prob_kaon_mpd[iTrack] < 0.1 && pid_tpc_prob_proton_mpd[iTrack] < 0.1){
            h_mass2[1][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            if (PDG_code_mc[id_from_mc_mpd[iTrack]] == 211 || PDG_code_mc[id_from_mc_mpd[iTrack]] == -211) h_PDG_mass2[1][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            else{
               h_bad_PDG[1][ptBin][etaBin]->Fill(PDG_code_mc[id_from_mc_mpd[iTrack]]);
               //if (PDG_code_mc[id_from_mc_mpd[iTrack]] > 1e6) std::cout << PDG_code_mc[id_from_mc_mpd[iTrack]] << std::endl;
            }
         }
         
         if (pid_tpc_prob_pion_mpd[iTrack] < 0.1 && pid_tpc_prob_kaon_mpd[iTrack] > 0.9 && pid_tpc_prob_proton_mpd[iTrack] < 0.1){
            h_mass2[2][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            if (PDG_code_mc[id_from_mc_mpd[iTrack]] == 321 || PDG_code_mc[id_from_mc_mpd[iTrack]] == -321) h_PDG_mass2[2][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            else{
               h_bad_PDG[2][ptBin][etaBin]->Fill(PDG_code_mc[id_from_mc_mpd[iTrack]]);
               //if (PDG_code_mc[id_from_mc_mpd[iTrack]] > 1e6) std::cout << PDG_code_mc[id_from_mc_mpd[iTrack]] << std::endl;
            }
         }
            
         if (pid_tpc_prob_pion_mpd[iTrack] < 0.1 && pid_tpc_prob_kaon_mpd[iTrack] < 0.1 && pid_tpc_prob_proton_mpd[iTrack] > 0.9){
            h_mass2[3][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            if (PDG_code_mc[id_from_mc_mpd[iTrack]] == 2212 || PDG_code_mc[id_from_mc_mpd[iTrack]] == -2212) h_PDG_mass2[2][ptBin][etaBin]->Fill(tof_mass2_mpd[iTrack]);
            else{
               h_bad_PDG[3][ptBin][etaBin]->Fill(PDG_code_mc[id_from_mc_mpd[iTrack]]);
               //if (PDG_code_mc[id_from_mc_mpd[iTrack]] > 1e6) std::cout << PDG_code_mc[id_from_mc_mpd[iTrack]] << std::endl;
            }
         }
         
      }//iTrack loop
      
   }//jentry loop
   
   TFile * outFile = new TFile("/home/peter/Documents/WorkLocal/MPD/RootFiles/pid_hists_m2.root","recreate");
   WriteAllHisto(outFile);
}

void PicoDstPidReader::InitAllHisto()
{
   std::cout << "Init Histograms..." << std::endl;
   InputTH1Info hInfo[Npid][bins->GetPtBinSize()][bins->GetEtaBinSize()];
   InputTH1Info hPDGInfo[Npid][bins->GetPtBinSize()][bins->GetEtaBinSize()];
   InputTH1Info hBadPDG[Npid][bins->GetPtBinSize()][bins->GetEtaBinSize()];
   char charTitle[200];
   
   for (int iPID=0; iPID<Npid; iPID++){
      for (int iPt=0; iPt<bins->GetPtBinSize();iPt++){
         for (int iEta=0;iEta<bins->GetEtaBinSize();iEta++){
            
            sprintf(charTitle,"m^{2} for %s (%2.2f < p_{T} < %2.2f [GeV/c]) (%2.2f < #eta < %2.2f);m^{2}, [GeV/c]^{2};N_{entries}",
                    s_pid[iPID].Data(),ptBins[iPt],ptBins[iPt+1],etaBins[iEta],etaBins[iEta+1]);
            hInfo[iPID][iPt][iEta]     = FillStruct("h_mass2_" + std::to_string(iPID) + "_" + std::to_string(iPt) + "_" + std::to_string(iEta),
                                                   TString(charTitle), 500, 0., 2.);
            
            sprintf(charTitle,"m^{2} (PDG) for %s (%2.2f < p_{T} < %2.2f [GeV/c]) (%2.2f < #eta < %2.2f);m^{2}, [GeV/c]^{2};N_{entries}",
                    s_pid[iPID].Data(),ptBins[iPt],ptBins[iPt+1],etaBins[iEta],etaBins[iEta+1]);
            hPDGInfo[iPID][iPt][iEta]  = FillStruct("h_mass2_PDG_" + std::to_string(iPID) + "_" + std::to_string(iPt) + "_" + std::to_string(iEta),
                                                   TString(charTitle), 500, 0., 2.);
            
            sprintf(charTitle,"Bad PDG for %s (%2.2f < p_{T} < %2.2f [GeV/c]) (%2.2f < #eta < %2.2f);PDG;N_{entries}",
                    s_pid[iPID].Data(),ptBins[iPt],ptBins[iPt+1],etaBins[iEta],etaBins[iEta+1]);
            hBadPDG[iPID][iPt][iEta]   = FillStruct("h_bad_PDG_" + std::to_string(iPID) + "_" + std::to_string(iPt) + "_" + std::to_string(iEta),
                                                   TString(charTitle), 8000, -4000., 4000.);
            
         }
      }
   }
   
   for (int iPID=0; iPID<Npid; iPID++){
      for (int iPt=0; iPt<bins->GetPtBinSize();iPt++){
         for (int iEta=0;iEta<bins->GetEtaBinSize();iEta++){
            
            h_mass2[iPID][iPt][iEta]      = InitTH1F(hInfo[iPID][iPt][iEta]);
            h_PDG_mass2[iPID][iPt][iEta]  = InitTH1F(hPDGInfo[iPID][iPt][iEta]);
            h_bad_PDG[iPID][iPt][iEta]    = InitTH1F(hBadPDG[iPID][iPt][iEta]);
            
         }
      }
   }
   
}

void PicoDstPidReader::WriteAllHisto(TFile* inFile)
{
   std::cout << "Writing Histograms..." << std::endl;
   inFile -> cd();
   for (int iPID=0; iPID<Npid; iPID++){
      for (int iPt=0; iPt<bins->GetPtBinSize();iPt++){
         for (int iEta=0;iEta<bins->GetEtaBinSize();iEta++){
            h_mass2[iPID][iPt][iEta] -> Write();
            h_PDG_mass2[iPID][iPt][iEta] -> Write();
            h_bad_PDG[iPID][iPt][iEta] -> Write();
         }
      }
   }
   inFile -> Close();
}
