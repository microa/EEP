#include <Arduino.h>
#include <ECG2_inferencing.h>
#include <ArduinoBLE.h>

/**Defines**/
//#define TRUE 1

/**BLE UUID**/
//const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
//const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

/**Static ECG data**/
static const float ecg_sample_data[][260] = {
{-0.890396959,-0.888897564,-0.865672188,-0.813936565,-0.761219454,-0.816808235,-0.885867685,-0.87967956,-0.741777987,-0.702117466,-0.74729627,-0.743882913,-0.73968568,-0.712743544,-0.682950747,-0.652286044,-0.623576063,-0.649531476,-0.674012406,-0.69357585,-0.614873465,-0.548126802,-0.508344883,-0.529590033,-0.565460826,-0.563379433,-0.549942351,-0.445682762,-0.442325485,-0.474881522,-0.509637742,-0.460452828,-0.394635232,-0.349042974,-0.369959838,-0.359860894,-0.342767223,-0.330070952,-0.30567727,-0.233250858,-0.241270476,-0.249773076,-0.286728995,-0.272898853,-0.194425534,-0.15792808,-0.149615886,-0.171876478,-0.164492363,-0.168198697,-0.153889256,-0.135304428,-0.111346262,-0.132669192,-0.164941132,-0.142765484,-0.10813475,-0.094903894,-0.097360029,-0.100086701,-0.102586437,-0.12458779,-0.114889025,-0.127048109,-0.142169552,-0.177547252,-0.210473868,-0.257169118,-0.245964892,-0.254862407,-0.259040247,-0.292410542,-0.325334666,-0.350619847,-0.3646585,-0.30706289,-0.31654457,-0.395065705,-0.490010684,-0.551730484,-0.524110058,-0.482582757,-0.426130967,-0.503043215,-0.60954085,-0.661538336,-0.665460328,-0.655865027,-0.630235282,-0.647519455,-0.64958511,-0.658031351,-0.666521555,-0.637705982,-0.632331939,-0.609233152,-0.580931311,-0.53906575,-0.500100525,-0.407155881,-0.369131546,-0.330950011,-0.303151677,-0.272179323,-0.242570523,-0.189598517,-0.143847905,-0.09879783,-0.037869403,0.082747068,0.236163006,0.451221544,0.694814958,0.899194317,1.102283094,1.317591915,1.548975909,1.801376752,2.08435376,2.40067251,2.663256947,2.957785252,3.248382084,3.577530366,3.894794825,4.080857317,4.201254104,4.312777573,4.393185057,4.406838564,4.390705229,4.362431693,4.395544781,4.361137209,4.228297318,4.135898942,4.006406174,3.713569854,3.359880083,2.965593973,2.5647952,2.29080507,2.072240506,1.862019845,1.682350288,1.526291637,1.386126008,1.341961156,1.305160873,1.184657466,1.067090964,1.034943854,1.064055768,1.215987755,1.523535944,1.669170944,1.710465527,1.327284955,0.776486446,0.145198755,-0.507136649,-0.915950816,-1.187360765,-1.269691251,-1.265346501,-1.27161528,-1.360421057,-1.52501267,-1.710545365,-1.73152694,-1.709655912,-1.639394653,-1.593819696,-1.658163356,-1.720187311,-1.792996545,-1.867273374,-1.919564493,-1.957887146,-2.024735885,-2.091685314,-2.142933661,-2.16505058,-2.193828431,-2.228087135,-2.240314871,-2.273063171,-2.30182645,-2.336707374,-2.334960643,-2.345678275,-2.381745737,-2.431324744,-2.492747336,-2.494708613,-2.480184988,-2.535452982,-2.550607986,-2.565066847,-2.589094052,-2.608501442,-2.612749365,-2.612578482,-2.617802074,-2.649159196,-2.637245356,-2.624680339,-2.553105262,-2.538317196,-2.524816624,-2.474513022,-2.451436678,-2.390884922,-2.330866047,-2.273811913,-2.246157764,-2.223601831,-2.180917792,-2.143337132,-2.041666154,-1.99943781,-1.976492932,-1.913468449,-1.82759129,-1.726964929,-1.656050507,-1.590833242,-1.520927081,-1.449410107,-1.365598044,-1.277439098,-1.1885988,-1.097551121,-1.018097033,-0.927767558,-0.845510826,-0.777318916,-0.68665316,-0.652573133,-0.637885206,-0.642888978,-0.623512209,-0.607785337,-0.595482838,-0.589211012,-0.584377984,-0.56983687,-0.617646068,-0.634843419,-0.562475165,-0.570712631,-0.565109392,-0.636106401,-0.649754578,-0.597743028,-0.581577822,-0.56644217,-0.545209042,-0.507183293,-0.542911955},
{-0.122386355,-0.130060127,-0.137532154,-0.142706656,-0.147831793,-0.145566039,-0.144860982,-0.154281655,-0.166552387,-0.163523461,-0.156295282,-0.157043789,-0.159483639,-0.160493914,-0.161206489,-0.160634809,-0.160010649,-0.158801064,-0.158076423,-0.161625205,-0.166604721,-0.172456504,-0.176944097,-0.186751509,-0.207162279,-0.177860929,-0.213666328,-0.22028643,-0.246543242,-0.190970632,-0.251712443,-0.250040721,-0.252393115,-0.260164489,-0.272404006,-0.273923733,-0.287384209,-0.295571279,-0.304045099,-0.311564789,-0.320028613,-0.321711282,-0.322386191,-0.342831131,-0.36733608,-0.381356148,-0.393941346,-0.386439601,-0.372971987,-0.403334007,-0.443344397,-0.447803795,-0.445013052,-0.43146961,-0.412772084,-0.451600559,-0.504934451,-0.488139226,-0.452615852,-0.454058753,-0.463752568,-0.467347506,-0.470045443,-0.467767284,-0.467392047,-0.460461661,-0.447877221,-0.493818717,-0.493170648,-0.525263257,-0.558884603,-0.589206238,-0.619500396,-0.653508607,-0.6825478,-0.729463947,-0.746415495,-0.757636047,-0.759230898,-0.831030403,-0.919191485,-0.912544088,-0.879509289,-0.900646433,-0.933971047,-0.950337926,-0.961042757,-0.978987944,-1.003863552,-0.98465517,-0.991534285,-1.023843302,-0.94623264,-0.924357433,-0.893933416,-0.844398397,-0.790791867,-0.720530123,-0.646389343,-0.643984968,-0.625592203,-0.627889821,-0.627514155,-0.591997129,-0.543452347,-0.398807131,-0.254064604,-0.183094986,-0.294109807,-0.311272006,-0.298696611,-0.100644357,0.213269035,0.496757784,0.851476452,1.470790605,2.199405526,2.878336856,3.457475224,3.663346509,3.572386873,3.363878005,2.856776512,1.756850347,0.568004015,-0.821266311,-2.411308838,-4.129959803,-5.310650276,-6.281725986,-6.96652979,-7.421642004,-7.667840109,-7.704815485,-7.613795737,-7.381078561,-6.864604825,-6.280654225,-5.641414755,-5.248678581,-4.930669131,-4.617577532,-4.313701419,-3.946180007,-3.552432554,-3.166100362,-2.793788568,-2.541237075,-2.33030479,-2.1126663,-1.909046339,-1.822290067,-1.759802509,-1.628010088,-1.457267196,-1.201581753,-1.143766235,-1.001398294,-0.830887322,-0.685125162,-0.553251619,-0.390741683,-0.230837766,-0.200854277,-0.212452785,-0.143162035,-0.074186848,0.010945923,-0.011266684,0.000387703,0.000772395,0.002333327,-0.004670713,0.016991822,0.045129951,-0.027930675,-0.119122916,-0.117869827,-0.10881637,-0.001280073,-0.063822895,-0.01622043,0.036349666,0.080752825,0.112896486,0.214147142,0.250773938,0.287151675,0.310882493,0.36820924,0.433119848,0.479806172,0.522309453,0.567848003,0.614606046,0.664636106,0.715077126,0.773061784,0.833981929,0.871537068,0.902837105,0.966045716,1.036707673,1.084615695,1.126030071,1.169208821,1.218426039,1.254094094,1.259413086,1.417186471,1.385533511,1.426260918,1.452116566,1.519748794,1.597657284,1.641093064,1.674802201,1.705947535,1.746668989,1.773050195,1.853858441,1.945124577,1.940504328,1.989736232,1.982579495,1.984949275,2.133479925,2.136941802,2.12387458,2.04586919,2.068366063,2.034593441,2.00200325,1.970856944,1.939324037,1.896345539,1.852435221,1.806604395,1.741879504,1.758358657,1.648372774,1.599883617,1.553032903,1.513007268,1.478756117,1.442955767,1.397907139,1.405455033,1.339014954,1.310195078,1.270738636,1.267849413,1.210524234,1.180509921,1.15022989,1.11600655,1.069683542,1.07702842,1.019427852,0.971165662},
{1.201031647,1.2332141,1.25521887,1.275138339,1.268372055,1.254981335,1.265902097,1.282601623,1.306482838,1.331876787,1.331320281,1.327123713,1.324596138,1.320604342,1.376318343,1.447437548,1.427006985,1.382197766,1.395209564,1.420950592,1.436340378,1.447754574,1.444745448,1.435131106,1.420015788,1.397243366,1.392996389,1.361141087,1.340295064,1.317764884,1.297807356,1.277857739,1.262122279,1.243693529,1.223050478,1.211351707,1.136314407,1.095797462,1.123469094,1.173137755,1.107677806,0.990537575,0.963804944,0.955850827,0.934035191,0.908282177,0.873280596,0.838654995,0.777642913,0.74459354,0.71132463,0.686288468,0.63658225,0.586163087,0.574085911,0.577201212,0.583702702,0.595340467,0.604344693,0.614564529,0.627734208,0.642776381,0.661586276,0.67885175,0.702296475,0.745687923,0.702586245,0.785167084,0.812320488,0.844288534,0.827526859,0.796865852,0.797110315,0.802383509,0.804750107,0.805458128,0.77938181,0.745322001,0.731391936,0.722693412,0.710894024,0.69895076,0.685665698,0.672520001,0.657942256,0.641776526,0.63725449,0.620108607,0.613807857,0.608142743,0.595264383,0.582090971,0.56985315,0.56029774,0.566444729,0.584228288,0.587737396,0.584183549,0.660872201,0.675341584,0.736558228,0.789011675,0.767291909,0.719756477,0.66592738,0.599166003,0.604891218,0.631512393,0.712011664,0.809946777,0.798239136,0.779783836,0.779953938,0.84000831,1.048523981,1.401108336,1.862744425,2.402980403,2.997373373,3.547910562,4.045913331,4.374717761,4.306783122,3.921930326,3.14505341,2.077901109,0.637555555,-0.944822769,-2.666095278,-4.331177934,-5.391468152,-6.134464995,-6.627302925,-6.899161994,-7.049863407,-7.087408366,-6.912813276,-6.863939992,-6.484106413,-6.006932545,-5.377860842,-4.792561683,-4.392647875,-4.06944543,-3.778739601,-3.510648989,-3.146059877,-2.767065052,-2.418387248,-2.102169423,-1.851536128,-1.6830315,-1.523231329,-1.38181556,-1.214852397,-1.045643962,-0.861776204,-0.680187525,-0.533906847,-0.404746779,-0.293867077,-0.1949162,-0.090780859,0.008239205,0.10323946,0.186261826,0.256866114,0.334434637,0.308801006,0.367490057,0.443490662,0.533061278,0.540929279,0.543801296,0.491114827,0.552907431,0.606092192,0.619949955,0.566135316,0.497747717,0.475951554,0.467295627,0.593864904,0.742014768,0.735898628,0.696888235,0.74814381,0.835745328,0.969336947,1.007754661,1.084404139,1.153014588,1.215627642,1.275007987,1.343263555,1.41448203,1.480898959,1.550546876,1.620178363,1.677013589,1.808703116,1.860853443,1.912139001,2.008526408,2.071707694,2.131779112,2.2414076,2.363015248,2.408890938,2.435998725,2.503606696,2.572973081,2.676008392,2.7169784,2.791588846,2.866763862,2.930540642,2.975293261,3.098000548,3.089482816,3.187132332,3.217718402,3.284458294,3.347891164,3.407450221,3.459552469,3.519303175,3.590841774,3.574974017,3.62991925,3.686171937,3.717726764,3.67720372,3.607440809,3.582068845,3.563856834,3.528965255,3.485964167,3.448143572,3.4086684,3.332820717,3.303105017,3.241561689,3.179710293,3.113211173,3.048279908,2.991647056,2.932138607,2.908013943,2.865422936,2.777616302,2.689604609,2.594641617,2.634386667,2.569279989,2.500407372,2.42208617,2.366864497,2.304436173,2.24396917},
{-0.972528072,-0.974295529,-0.977134351,-0.978406657,-0.96967925,-0.959387325,-0.945182641,-0.933311046,-0.944120314,-0.964690676,-0.988316778,-1.015371179,-1.040635714,-1.065729187,-1.093045847,-1.120236499,-1.14312544,-1.164095357,-1.183382005,-1.201470202,-1.220548119,-1.238565094,-1.257044485,-1.27374215,-1.282597139,-1.287065962,-1.290058333,-1.291147595,-1.286819131,-1.283436361,-1.278034267,-1.272236409,-1.262996532,-1.253466536,-1.248417713,-1.250283539,-1.243448302,-1.233051836,-1.224138939,-1.212137993,-1.18670868,-1.15451616,-1.11911297,-1.080354997,-1.040757922,-0.999759236,-0.956435557,-0.911999231,-0.868584189,-0.825249363,-0.781714704,-0.738424675,-0.69426346,-0.649190118,-0.609979918,-0.563866389,-0.523527814,-0.484028155,-0.446858579,-0.410973442,-0.373345212,-0.337074437,-0.301134346,-0.267902852,-0.245420658,-0.22850623,-0.213982151,-0.202291016,-0.192062853,-0.183085647,-0.176931366,-0.171647624,-0.162897409,-0.15356751,-0.143345332,-0.133461784,-0.128532994,-0.124989151,-0.122851794,-0.120795373,-0.112182893,-0.100942832,-0.092846492,-0.084980751,-0.072087443,-0.060227453,-0.046076343,-0.03543566,-0.047057724,-0.068685451,-0.09287776,-0.120403894,-0.148026402,-0.175337261,-0.204197768,-0.23127273,-0.250136521,-0.262040816,-0.272967261,-0.280040061,-0.28097815,-0.277960839,-0.269361108,-0.257082604,-0.249336089,-0.240653523,-0.223812201,-0.201856978,-0.179798236,-0.150585765,-0.119308865,-0.077562841,-0.001545885,0.092604616,0.201750552,0.321791855,0.43645637,0.556773132,0.679435045,0.810137979,0.972500014,1.148745661,1.329618228,1.513680598,1.69020109,1.861123339,2.033214253,2.196873085,2.343640966,2.481555082,2.575011694,2.645722718,2.795244297,2.946694485,2.994459972,2.996523091,2.955850982,2.909751005,2.826905826,2.730468611,2.640443032,2.55691952,2.466079644,2.388719875,2.358482172,2.354290751,2.404954264,2.464618463,2.52065029,2.538558313,2.473491687,2.335552332,2.032836024,1.653826546,1.231255257,0.796614919,0.435777525,0.119346195,-0.13443305,-0.340059702,-0.501484041,-0.623823613,-0.719591037,-0.787533045,-0.82134936,-0.838635166,-0.827250832,-0.810157926,-0.852311558,-0.914457901,-0.976073068,-1.039956105,-1.092584737,-1.138880658,-1.186430159,-1.229390839,-1.254910345,-1.271218406,-1.285027473,-1.294478289,-1.298656002,-1.300856125,-1.298026685,-1.295074288,-1.305919717,-1.321814736,-1.338351908,-1.355770624,-1.37037309,-1.383507774,-1.396847022,-1.408939234,-1.417437061,-1.423783867,-1.427723573,-1.429866312,-1.432526035,-1.433736807,-1.433831926,-1.431680906,-1.423134168,-1.410857573,-1.396649525,-1.380179332,-1.361801175,-1.341923502,-1.319911139,-1.296742334,-1.275038571,-1.253273791,-1.230397187,-1.206757938,-1.182277001,-1.156719909,-1.130876571,-1.103934338,-1.073790778,-1.042471252,-1.008587827,-0.971951553,-0.946366251,-0.908026605,-0.876720514,-0.844527297,-0.808089951,-0.769830356,-0.733220414,-0.696807329,-0.658265678,-0.620656496,-0.582372106,-0.546495033,-0.522463421,-0.504267312,-0.488773369,-0.476150437,-0.463980481,-0.452988671,-0.444284348,-0.436747377,-0.428397147,-0.420357491,-0.412663815,-0.405549734,-0.400314863,-0.395827744,-0.392120575,-0.388451553,-0.383319634,-0.37836065,-0.369698337,-0.36630143,-0.360131293,-0.354383605,-0.348734708,-0.343489699,-0.339640765,-0.336600577,-0.333409051,-0.329970166},
{-0.001345298,0.001858601,0.006110626,0.010801482,0.015941108,0.020984982,0.026122672,0.0315691,0.035817366,0.042980144,0.057160487,0.038867603,0.05782545,0.074115734,0.065629861,0.073038782,0.08021452,0.084797364,0.088366945,0.091925303,0.095255656,0.099131856,0.103074765,0.106567131,0.109932479,0.113071909,0.11552359,0.120026907,0.12701028,0.120739526,0.105009216,0.140440904,0.116483008,0.092904431,0.144037054,0.154625708,0.156371957,0.181141914,0.16609608,0.11732769,0.138867917,0.129629882,0.125811136,0.124933808,0.128515161,0.125912473,0.12264944,0.118977998,0.115960296,0.117822064,0.121617777,0.127142502,0.133385272,0.136481052,0.139147041,0.141310123,0.143854447,0.151661009,0.161771583,0.169485285,0.176284306,0.189719527,0.197151759,0.208565659,0.216571993,0.208849604,0.194660191,0.171192488,0.152312704,0.130350814,0.10695844,0.084344493,0.066387182,0.02298789,0.013694523,-0.011212603,-0.032625823,-0.067736232,-0.08520116,-0.120618476,-0.131244616,-0.166030302,-0.152900184,-0.161949798,-0.166249942,-0.159262348,-0.149243105,-0.134590864,-0.119409257,-0.131609491,-0.149605474,-0.153390735,-0.15801506,-0.19087809,-0.21846552,-0.287523839,-0.356261498,-0.233848069,-0.068799565,0.007648743,-0.001138307,-0.031579088,-0.043476079,0.047359873,0.238643691,0.306135928,0.363925688,0.374752409,0.457073309,0.534328059,0.625606483,0.695520341,0.76860723,0.843631345,0.956754369,1.057716133,1.031768227,0.952673679,0.876484961,0.715317327,0.440542876,-0.022466749,-0.850679176,-2.023803011,-3.194200391,-3.963348858,-4.395028227,-4.543808427,-4.58718748,-4.695836643,-4.774488527,-4.764896999,-4.687492357,-4.528381043,-4.266758286,-4.018429877,-3.641492535,-3.376059186,-3.202320417,-3.021603859,-2.840760191,-2.646170033,-2.378910059,-2.104575934,-1.884477793,-1.719486582,-1.574252669,-1.463459361,-1.364630778,-1.236479209,-1.117585633,-0.942814478,-0.837781493,-0.782772269,-0.756232914,-0.751774349,-0.749907465,-0.664312269,-0.535634427,-0.444886414,-0.267731651,-0.140488592,-0.051078686,0.096669795,0.19498394,0.298410199,0.3916443,0.474556097,0.556900778,0.640505369,0.722978512,0.802548079,0.87983683,0.949615391,1.011845681,1.087720798,1.137363505,1.196703177,1.252374501,1.303391882,1.35093388,1.39753441,1.441428457,1.483138913,1.521740123,1.553361332,1.579611219,1.606433898,1.634985258,1.637775198,1.667988799,1.678887019,1.690131178,1.709794508,1.732159939,1.754269487,1.776033761,1.793779823,1.809150119,1.824109567,1.839373541,1.845910031,1.863514258,1.871045745,1.876889242,1.884359449,1.88966045,1.893819463,1.893965998,1.880137623,1.858665415,1.833676167,1.804262461,1.772016471,1.737155198,1.696560955,1.663468414,1.610836372,1.583767992,1.546911636,1.523994554,1.432959965,1.431561586,1.383223175,1.331852995,1.280148025,1.227271082,1.170122444,1.111382249,1.05585888,1.000372048,0.945171692,0.888925466,0.826925712,0.763932633,0.695493087,0.638251077,0.572127623,0.510134127,0.437782174,0.383187794,0.342927865,0.313043685,0.290400325,0.276889489,0.246599429,0.243964488,0.228624599,0.20745556,0.226973019,0.198252037,0.179680438,0.179745663,0.187778655,0.169608451,0.171223126,0.177953913,0.155031361,0.164573622,0.156435945},

}; 


/**Adjusted inference structure for 2D array**/
typedef struct {
  const float (*buffer)[260];  // Pointer to a 2D array
  uint32_t buf_count;
  uint32_t n_samples;
  uint32_t n_rows;
} inference_t;

/**Initialize inference structure for 2D array**/
static inference_t inference = {
  ecg_sample_data,
  0,
  sizeof(ecg_sample_data[0]) / sizeof(ecg_sample_data[0][0]),
  sizeof(ecg_sample_data) / sizeof(ecg_sample_data[0])
};

static bool debug_nn = false;


/**Power Saver**/
void PowerSave_Settings(void){
  ///Saves 4mA
  digitalWrite(LED_PWR, LOW);   //Turn off the power LED
  digitalWrite(PIN_ENABLE_SENSORS_3V3, LOW);    //Turn off the sensors
  digitalWrite(PIN_ENABLE_I2C_PULLUP, LOW);   //Turn off the I2C pull-up resistors
}

/**Serial Settings
void Serial_Settings(void){
  Serial.begin(9600);
  while (!Serial);  
}**/


/**BLE Pre-Settings**/
void BLE_Settings(void){
  if (!BLE.begin()) {
    while (1);
  }

  String dataToSend = "x"; 
  BLE.setLocalName(dataToSend.c_str());
  BLE.setAdvertisedServiceUuid("180C");
  BLE.advertise();
  BLE.end();
}


/**Get raw ECG signal data for a specific row in the 2D array**/
static int ecg_signal_get_data(size_t offset, size_t length, float *out_ptr) {
  if (offset + length > inference.n_samples) {
      return -1; // Out of range
  }
  for (size_t i = 0; i < length; ++i) {
      out_ptr[i] = inference.buffer[inference.buf_count][offset + i];
  }
  return 0;
}


/************************************/
void Inference_BLE(){

  BLE.end();
  while(1){
    for (uint32_t row = 0; row < inference.n_rows; ++row) {
      //Serial.println(String(row));

      signal_t signal;
      signal.total_length = inference.n_samples;
      inference.buf_count = row; // Set the current row to process
      signal.get_data = &ecg_signal_get_data;
      ei_impulse_result_t result = {0};

      EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
      if (r != EI_IMPULSE_OK) {
          continue; // Skip to next iteration
      }
    }

  }


    
  BLE.end();
  //delay(1000);
  //while(!BLE.begin());
  delay(100000);
}


/************************************/
void setup(){
  //Serial_Settings();
  PowerSave_Settings();
  BLE_Settings();
}

/************************************/
void loop() {
  Inference_BLE();
}

/************************************/
int main(void){
  init();
  initVariant();

  //Disabling UART0 (saves around 300-500��A)
  NRF_UART0->TASKS_STOPTX = 1;
  NRF_UART0->TASKS_STOPRX = 1;
  NRF_UART0->ENABLE = 0;
  //NRF_POWER->SYSTEMOFF = 1;

  *(volatile uint32_t *)0x40002FFC = 0;
  *(volatile uint32_t *)0x40002FFC;
  *(volatile uint32_t *)0x40002FFC = 1; //Setting up UART registers again due to a library issue

  //Removing USB CDC feature
  //#if defined(SERIAL_CDC)
  //  PluggableUSBD().begin();
  //  SerialUSB.begin(115200);
  //#endif

  setup();
  for(;;){
    loop();
  //If you won't be using serial communication comment next line
  //    if(arduino::serialEventRun) arduino::serialEventRun();
  }
  return 0;
}



