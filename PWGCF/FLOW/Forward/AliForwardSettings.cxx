#include "TString.h"
#include "TMath.h"
#include "AliForwardSettings.h"
#include "TFile.h"

//________________________________________________________________________
AliForwardSettings::AliForwardSettings() :
  fPhiAcceptanceLowEdge(0),
  fPhiAcceptanceUpEdge(2*TMath::Pi()),  
  fNPhiBins(20),
  fEtaLowEdge(-3.36),
  fEtaUpEdge(4.8),
  fZVtxAcceptanceLowEdge(-10),
  fZVtxAcceptanceUpEdge(10),
  fNZvtxBins(10),
  fnoSamples(10),
  fNRefEtaBins(1),
  fNDiffEtaBins(34),
  fCentBins(80),
  fCentUpEdge(80),
  nuacentral(),
  nuaforward(),
  seccorr_fwd(),
  seccorr_cent(),
  nuehist(),
  doNUA(true),
  doNUE(false),
  gap(0.0),
  minpt(0.2),
  maxpt(5),
  mc(kFALSE),
  esd(kFALSE),
  tracktype(kGlobalComb),
  nua_mode(kInterpolate),
  ref_mode(kTPCref),
  useTPC{kTRUE},
  useSPD(kFALSE),
  useITS(kFALSE),
  use_primaries_cen(kFALSE),
  use_primaries_fwd(kFALSE),
  use_primaries_fwdref(kFALSE),
  useEventcuts(kTRUE),
  centrality_estimator("V0M"),//CL0, V0M
  etagap(kTRUE),
  makeFakeHoles(kFALSE),
  fnoClusters(70),
  fCutChargedDCAxyMax(0.),
  fCutChargedDCAzMax(2.),
  doPt(kFALSE),
  stdQC(kFALSE),
  sec_corr(kTRUE),
  a5(kFALSE),
  fileName(""),
  fMaxConsequtiveStrips(2),
  standard_only(kTRUE),
  fmdlowcut(2.0),
  fmdhighcut(3.2),
  track_sample(0),
  nua_runnumber(0),
  correct_nua_mc(),
  run_list(0),
  second_analysis(kFALSE),
  SC_analysis(kFALSE),
  decorr_analysis(kFALSE),
  normal_analysis(kTRUE)
{
}
