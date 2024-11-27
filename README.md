## DSCEE (Decentralized Signal Classification using Early Exit)

### Experimental Code <br>
Deep sleep mode: [code](Code/DeepSleep(idle_mode).cpp) <br>
Inference mode: [code](Code/bk_vtx001_noBLE_Infer_noidle.cpp) <br>
Inference idle mode: [code](Code/bk_vtx001_noBLE_Infer_idle.cpp) <br>
Connected mode: [code](Code/bk_vtx001a_connected_noinfer_idle_keepconnected.cpp) <br>

### Training Code <br>
To be continue... <br>
 
### Deploy in Embedded System <br>
Trained model: [2Layerswith96%Acc.zip](inference/2Layerswith96%Acc.zip) <br>
Step1. Launch Arduino IDE (my version is 2.3.3)
Step2. Sketch -> Include Library -> Add .ZIP Library -> (add above trained model)
Step3. Tools -> Manage Libraries -> search "ArduinoBLE" -> install (my version is 1.3.7)
Step4. Include the inference file on your code (code example provided above, see Experimental Code - Inference mode)

### Replicate Guide <br>
To be continue... <br>



* If you find our article is useful to your research, please cite following papers: <br>
```
Once the paper is accepted, we will release the citation details.
```
<!-- 
```bibtex
@inproceedings{xiaolin2024,
  title={Decentralized Multistage Biomedical Signal Classification using Early Exits},
  author={Xiaolin Li, Binhua Huang, Barry Cardiff, Deepu John},
  booktitle={Has not been accepted by any journal yet},
  pages={100--120},
  year={2024},
  organization={NONE}
}
```
-->

