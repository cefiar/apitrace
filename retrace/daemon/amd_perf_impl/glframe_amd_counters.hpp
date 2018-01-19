#include <map>
#include <string>
#include <vector>

struct AMDMetricId {
  int group;
  int counter;
};

class AMDMetric {
 public:
  typedef std::map<std::string, AMDMetric> MetricIdMap;
  virtual ~AMDMetric() {}
  virtual const std::string &name() const = 0;
  virtual const std::string &description() const = 0;
  virtual void selectCounters(const std::vector<unsigned int> &monitors,
                              const MetricIdMap &ids) const = 0;
  virtual float parseMetric(const std::vector<unsigned char> &buffer) const;
  static void init();
  static const std::map<const std::string, const AMDMetric *> metrics;
};

class HSTime : public AMDMetric {
  // 15124 , GPUTime_BOTTOM_TO_BOTTOM , gpa_uint64
  // 3268 , SPI_SPI_PERF_HS_BUSY , gpa_uint64
  // 3274 , SPI_SPI_PERF_HS_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // p.DefinePublicCounter("HSTime", "#Timing#Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
};
class DSBusy : public AMDMetric {
  // 3231 , SPI_SPI_PERF_VS_BUSY , gpa_uint64
  // 3256 , SPI_SPI_PERF_ES_BUSY , gpa_uint64
  // 3300 , SPI_SPI_PERF_PS_CTL_BUSY , gpa_uint64
  // 3262 , SPI_SPI_PERF_ES_WAVE , gpa_uint64
  // 3284 , SPI_SPI_PERF_LS_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("DSBusy", "#Timing#The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min");
};
class DSTime : public AMDMetric {
  // 15124 , GPUTime_BOTTOM_TO_BOTTOM , gpa_uint64
  // 3231 , SPI_SPI_PERF_VS_BUSY , gpa_uint64
  // 3256 , SPI_SPI_PERF_ES_BUSY , gpa_uint64
  // 3300 , SPI_SPI_PERF_PS_CTL_BUSY , gpa_uint64
  // 3262 , SPI_SPI_PERF_ES_WAVE , gpa_uint64
  // 3284 , SPI_SPI_PERF_LS_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("DSTime", "#Timing#Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*");
};
class GSBusy : public AMDMetric {
  // 3247 , SPI_SPI_PERF_GS_BUSY , gpa_uint64
  // 3250 , SPI_SPI_PERF_GS_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("GSBusy", "#Timing#The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
};
class GSTime : public AMDMetric {
  // 15124 , GPUTime_BOTTOM_TO_BOTTOM , gpa_uint64
  // 3247 , SPI_SPI_PERF_GS_BUSY , gpa_uint64
  // 3250 , SPI_SPI_PERF_GS_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("GSTime", "#Timing#Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
};
class PSBusy : public AMDMetric {
  // 3300 , SPI_SPI_PERF_PS_CTL_BUSY , gpa_uint64
  // 3305 , SPI_SPI_PERF_PS_CTL_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("PSBusy", "#Timing#The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
};
class PSTime : public AMDMetric {
  // 15124 , GPUTime_BOTTOM_TO_BOTTOM , gpa_uint64
  // 3300 , SPI_SPI_PERF_PS_CTL_BUSY , gpa_uint64
  // 3305 , SPI_SPI_PERF_PS_CTL_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("PSTime", "#Timing#Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
};
class CSBusy : public AMDMetric {
  // 3288 , SPI_SPI_PERF_CSG_BUSY , gpa_uint64
  // 3292 , SPI_SPI_PERF_CSG_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("CSBusy", "#Timing#The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
};
class CSTime : public AMDMetric {
  // 15124 , GPUTime_BOTTOM_TO_BOTTOM , gpa_uint64
  // 3288 , SPI_SPI_PERF_CSG_BUSY , gpa_uint64
  // 3292 , SPI_SPI_PERF_CSG_WAVE , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("CSTime", "#Timing#Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
};
class VSVerticesIn : public AMDMetric {
  // 14800 , VGT_VGT_PERF_VGT_SPI_VSVERT_SEND , gpa_uint64
  // 14781 , VGT_VGT_PERF_VGT_SPI_ESVERT_VALID , gpa_uint64
  // 14876 , VGT_VGT_PERF_VGT_SPI_LSVERT_VALID , gpa_uint64

        // p.DefinePublicCounter("VSVerticesIn", "#VertexShader#The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
};
class VSVALUInstCount : public AMDMetric {
  // 4350 , SQ_VS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 4328 , SQ_VS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3752 , SQ_ES_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 3730 , SQ_ES_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4948 , SQ_LS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 4926 , SQ_LS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("VSVALUInstCount", "#VertexShader#Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
};
class VSSALUInstCount : public AMDMetric {
  // 4354 , SQ_VS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 4328 , SQ_VS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3756 , SQ_ES_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 3730 , SQ_ES_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4952 , SQ_LS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 4926 , SQ_LS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("VSSALUInstCount", "#VertexShader#Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
};
class VSVALUBusy : public AMDMetric {
  // 4405 , SQ_VS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
  // 3807 , SQ_ES_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("VSVALUBusy", "#VertexShader#The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*");
};
class VSSALUBusy : public AMDMetric {
  // 4410 , SQ_VS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
  // 3812 , SQ_ES_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("VSSALUBusy", "#VertexShader#The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,3,/,(100),*");
};
class HSPatches : public AMDMetric {
  // 14885 , VGT_VGT_PERF_VGT_SPI_HSVERT_VALID , gpa_uint64

        // p.DefinePublicCounter("HSPatches", "#HullShader#The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class HSVALUInstCount : public AMDMetric {
  // 5247 , SQ_HS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 5225 , SQ_HS_SQ_PERF_SEL_WAVES , gpa_uint64

        // p.DefinePublicCounter("HSVALUInstCount", "#HullShader#Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class HSSALUInstCount : public AMDMetric {
  // 5251 , SQ_HS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 5225 , SQ_HS_SQ_PERF_SEL_WAVES , gpa_uint64

        // p.DefinePublicCounter("HSSALUInstCount", "#HullShader#Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class HSVALUBusy : public AMDMetric {
  // 5302 , SQ_HS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("HSVALUBusy", "#HullShader#The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
};
class HSSALUBusy : public AMDMetric {
  // 5307 , SQ_HS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64

        // p.DefinePublicCounter("HSSALUBusy", "#HullShader#The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
};
class DSVerticesIn : public AMDMetric {
  // 14800 , VGT_VGT_PERF_VGT_SPI_VSVERT_SEND , gpa_uint64
  // 14781 , VGT_VGT_PERF_VGT_SPI_ESVERT_VALID , gpa_uint64
  // 14876 , VGT_VGT_PERF_VGT_SPI_LSVERT_VALID , gpa_uint64

        // p.DefinePublicCounter("DSVerticesIn", "#DomainShader#The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
};
class DSVALUInstCount : public AMDMetric {
  // 4350 , SQ_VS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 4328 , SQ_VS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3752 , SQ_ES_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
  // 3730 , SQ_ES_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("DSVALUInstCount", "#DomainShader#Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
};
class DSSALUInstCount : public AMDMetric {
  // 4354 , SQ_VS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 4328 , SQ_VS_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3756 , SQ_ES_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
  // 3730 , SQ_ES_SQ_PERF_SEL_WAVES , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("DSSALUInstCount", "#DomainShader#Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
};
class DSVALUBusy : public AMDMetric {
  // 4405 , SQ_VS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
  // 3807 , SQ_ES_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("DSVALUBusy", "#DomainShader#The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*");
};
class DSSALUBusy : public AMDMetric {
  // 4410 , SQ_VS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
  // 3812 , SQ_ES_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
  // 3740 , SQ_ES_SQ_PERF_SEL_ITEMS , gpa_uint64
  // 4936 , SQ_LS_SQ_PERF_SEL_ITEMS , gpa_uint64

        // p.DefinePublicCounter("DSSALUBusy", "#DomainShader#The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*");
};
class GSPrimsIn : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 14789 , VGT_VGT_PERF_VGT_SPI_GSPRIM_VALID , gpa_uint64
        // internalCounters.push_back(14789);

        // p.DefinePublicCounter("GSPrimsIn", "#GeometryShader#The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class GSVerticesOut : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 14800 , VGT_VGT_PERF_VGT_SPI_VSVERT_SEND , gpa_uint64
        // internalCounters.push_back(14800);
  // 14781 , VGT_VGT_PERF_VGT_SPI_ESVERT_VALID , gpa_uint64
        // internalCounters.push_back(14781);

        // p.DefinePublicCounter("GSVerticesOut", "#GeometryShader#The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
};
class GSVALUInstCount : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4051 , SQ_GS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
        // internalCounters.push_back(4051);
  // 4029 , SQ_GS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(4029);

        // p.DefinePublicCounter("GSVALUInstCount", "#GeometryShader#Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class GSSALUInstCount : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4055 , SQ_GS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
        // internalCounters.push_back(4055);
  // 4029 , SQ_GS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(4029);

        // p.DefinePublicCounter("GSSALUInstCount", "#GeometryShader#Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class GSVALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4106 , SQ_GS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
        // internalCounters.push_back(4106);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("GSVALUBusy", "#GeometryShader#The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
};
class GSSALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4111 , SQ_GS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
        // internalCounters.push_back(4111);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("GSSALUBusy", "#GeometryShader#The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
};
class PrimitiveAssemblyBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2785 , PA_SU_PERF_PAPC_CLIP_BUSY , gpa_uint64
        // internalCounters.push_back(2785);
  // 2789 , PA_SU_PERF_PAPC_SU_STALLED_SC , gpa_uint64
        // internalCounters.push_back(2789);
  // 2741 , PA_SU_PERF_PAPC_SU_OUTPUT_PRIM , gpa_uint64
        // internalCounters.push_back(2741);
  // 2753 , PA_SU_PERF_PAPC_SU_OUTPUT_PRIM_DUAL , gpa_uint64
        // internalCounters.push_back(2753);
  // 2742 , PA_SU_PERF_PAPC_SU_OUTPUT_CLIP_PRIM , gpa_uint64
        // internalCounters.push_back(2742);
  // 2754 , PA_SU_PERF_PAPC_SU_OUTPUT_CLIP_PRIM_DUAL , gpa_uint64
        // internalCounters.push_back(2754);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("PrimitiveAssemblyBusy", "#Timing#The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
};
class PrimitivesIn : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2688 , PA_SU_PERF_PAPC_PA_INPUT_PRIM , gpa_uint64
        // internalCounters.push_back(2688);

        // p.DefinePublicCounter("PrimitivesIn", "#PrimitiveAssembly#The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class CulledPrims : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2694 , PA_SU_PERF_PAPC_CLPR_CULL_PRIM , gpa_uint64
        // internalCounters.push_back(2694);
  // 2734 , PA_SU_PERF_PAPC_SU_ZERO_AREA_CULL_PRIM , gpa_uint64
        // internalCounters.push_back(2734);
  // 2735 , PA_SU_PERF_PAPC_SU_BACK_FACE_CULL_PRIM , gpa_uint64
        // internalCounters.push_back(2735);
  // 2736 , PA_SU_PERF_PAPC_SU_FRONT_FACE_CULL_PRIM , gpa_uint64
        // internalCounters.push_back(2736);
  // 2737 , PA_SU_PERF_PAPC_SU_POLYMODE_FACE_CULL , gpa_uint64
        // internalCounters.push_back(2737);

        // p.DefinePublicCounter("CulledPrims", "#PrimitiveAssembly#The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+");
};
class ClippedPrims : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2701 , PA_SU_PERF_PAPC_CLPR_VVUCP_CLIP_PRIM , gpa_uint64
        // internalCounters.push_back(2701);

        // p.DefinePublicCounter("ClippedPrims", "#PrimitiveAssembly#The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class PAStalledOnRasterizer : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2789 , PA_SU_PERF_PAPC_SU_STALLED_SC , gpa_uint64
        // internalCounters.push_back(2789);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("PAStalledOnRasterizer", "#PrimitiveAssembly#Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
};
class PSPixelsOut : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5831 , SX_SX_PERF_SEL_DB0_PIXELS , gpa_uint64
        // internalCounters.push_back(5831);
  // 5836 , SX_SX_PERF_SEL_DB1_PIXELS , gpa_uint64
        // internalCounters.push_back(5836);
  // 5841 , SX_SX_PERF_SEL_DB2_PIXELS , gpa_uint64
        // internalCounters.push_back(5841);
  // 5846 , SX_SX_PERF_SEL_DB3_PIXELS , gpa_uint64
        // internalCounters.push_back(5846);

        // p.DefinePublicCounter("PSPixelsOut", "#PixelShader#Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PSExportStalls : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5833 , SX_SX_PERF_SEL_DB0_PIXEL_STALL , gpa_uint64
        // internalCounters.push_back(5833);
  // 5838 , SX_SX_PERF_SEL_DB1_PIXEL_STALL , gpa_uint64
        // internalCounters.push_back(5838);
  // 5843 , SX_SX_PERF_SEL_DB2_PIXEL_STALL , gpa_uint64
        // internalCounters.push_back(5843);
  // 5848 , SX_SX_PERF_SEL_DB3_PIXEL_STALL , gpa_uint64
        // internalCounters.push_back(5848);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("PSExportStalls", "#PixelShader#Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
};
class PSVALUInstCount : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4649 , SQ_PS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
        // internalCounters.push_back(4649);
  // 4627 , SQ_PS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(4627);

        // p.DefinePublicCounter("PSVALUInstCount", "#PixelShader#Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class PSSALUInstCount : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4653 , SQ_PS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
        // internalCounters.push_back(4653);
  // 4627 , SQ_PS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(4627);

        // p.DefinePublicCounter("PSSALUInstCount", "#PixelShader#Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
};
class PSVALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4704 , SQ_PS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
        // internalCounters.push_back(4704);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("PSVALUBusy", "#PixelShader#The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
};
class PSSALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 4709 , SQ_PS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
        // internalCounters.push_back(4709);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("PSSALUBusy", "#PixelShader#The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
};
class CSThreadGroups : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSThreadGroups", "#ComputeShader#Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class CSWavefronts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSWavefronts", "#ComputeShader#The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class CSThreads : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5534 , SQ_CS_SQ_PERF_SEL_ITEMS , gpa_uint64
        // internalCounters.push_back(5534);

        // p.DefinePublicCounter("CSThreads", "#ComputeShader#The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
};
class CSVALUInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5546 , SQ_CS_SQ_PERF_SEL_INSTS_VALU , gpa_uint64
        // internalCounters.push_back(5546);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSVALUInsts", "#ComputeShader#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
};
class CSVALUUtilization : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5609 , SQ_CS_SQ_PERF_SEL_THREAD_CYCLES_VALU , gpa_uint64
        // internalCounters.push_back(5609);
  // 5601 , SQ_CS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
        // internalCounters.push_back(5601);

        // p.DefinePublicCounter("CSVALUUtilization", "#ComputeShader#The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min");
};
class CSSALUInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5550 , SQ_CS_SQ_PERF_SEL_INSTS_SALU , gpa_uint64
        // internalCounters.push_back(5550);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSSALUInsts", "#ComputeShader#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
};
class CSVFetchInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5548 , SQ_CS_SQ_PERF_SEL_INSTS_VMEM_RD , gpa_uint64
        // internalCounters.push_back(5548);
  // 5954 , TA0_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(5954);
  // 6073 , TA1_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6073);
  // 6192 , TA2_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6192);
  // 6311 , TA3_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6311);
  // 6430 , TA4_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6430);
  // 6549 , TA5_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6549);
  // 6668 , TA6_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6668);
  // 6787 , TA7_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6787);
  // 6906 , TA8_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6906);
  // 7025 , TA9_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7025);
  // 7144 , TA10_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7144);
  // 7263 , TA11_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7263);
  // 7382 , TA12_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7382);
  // 7501 , TA13_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7501);
  // 7620 , TA14_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7620);
  // 7739 , TA15_TA_PERF_SEL_FLAT_READ_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7739);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSVFetchInsts", "#ComputeShader#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero");
};
class CSSFetchInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5551 , SQ_CS_SQ_PERF_SEL_INSTS_SMEM , gpa_uint64
        // internalCounters.push_back(5551);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSSFetchInsts", "#ComputeShader#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
};
class CSVWriteInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5547 , SQ_CS_SQ_PERF_SEL_INSTS_VMEM_WR , gpa_uint64
        // internalCounters.push_back(5547);
  // 5955 , TA0_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(5955);
  // 6074 , TA1_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6074);
  // 6193 , TA2_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6193);
  // 6312 , TA3_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6312);
  // 6431 , TA4_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6431);
  // 6550 , TA5_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6550);
  // 6669 , TA6_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6669);
  // 6788 , TA7_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6788);
  // 6907 , TA8_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(6907);
  // 7026 , TA9_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7026);
  // 7145 , TA10_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7145);
  // 7264 , TA11_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7264);
  // 7383 , TA12_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7383);
  // 7502 , TA13_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7502);
  // 7621 , TA14_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7621);
  // 7740 , TA15_TA_PERF_SEL_FLAT_WRITE_WAVEFRONTS , gpa_uint64
        // internalCounters.push_back(7740);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSVWriteInsts", "#ComputeShader#The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero");
};
class CSFlatVMemInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5552 , SQ_CS_SQ_PERF_SEL_INSTS_FLAT , gpa_uint64
        // internalCounters.push_back(5552);
  // 5553 , SQ_CS_SQ_PERF_SEL_INSTS_FLAT_LDS_ONLY , gpa_uint64
        // internalCounters.push_back(5553);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSFlatVMemInsts", "#ComputeShader#The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
};
class CSVALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5601 , SQ_CS_SQ_PERF_SEL_INST_CYCLES_VALU , gpa_uint64
        // internalCounters.push_back(5601);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("CSVALUBusy", "#ComputeShader#The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
};
class CSSALUBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5606 , SQ_CS_SQ_PERF_SEL_INST_CYCLES_SALU , gpa_uint64
        // internalCounters.push_back(5606);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("CSSALUBusy", "#ComputeShader#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
};
class CSMemUnitBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5868 , TA0_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(5868);
  // 5987 , TA1_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(5987);
  // 6106 , TA2_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6106);
  // 6225 , TA3_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6225);
  // 6344 , TA4_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6344);
  // 6463 , TA5_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6463);
  // 6582 , TA6_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6582);
  // 6701 , TA7_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6701);
  // 6820 , TA8_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6820);
  // 6939 , TA9_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6939);
  // 7058 , TA10_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7058);
  // 7177 , TA11_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7177);
  // 7296 , TA12_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7296);
  // 7415 , TA13_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7415);
  // 7534 , TA14_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7534);
  // 7653 , TA15_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7653);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSMemUnitBusy", "#ComputeShader#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,ifnotzero");
};
class CSMemUnitStalled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 11782 , TCP0_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(11782);
  // 11962 , TCP1_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(11962);
  // 12142 , TCP2_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(12142);
  // 12322 , TCP3_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(12322);
  // 12502 , TCP4_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(12502);
  // 12682 , TCP5_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(12682);
  // 12862 , TCP6_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(12862);
  // 13042 , TCP7_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13042);
  // 13222 , TCP8_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13222);
  // 13402 , TCP9_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13402);
  // 13582 , TCP10_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13582);
  // 13762 , TCP11_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13762);
  // 13942 , TCP12_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(13942);
  // 14122 , TCP13_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(14122);
  // 14302 , TCP14_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(14302);
  // 14482 , TCP15_TCP_PERF_SEL_TCP_TA_DATA_STALL_CYCLES , gpa_uint64
        // internalCounters.push_back(14482);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSMemUnitStalled", "#ComputeShader#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,ifnotzero");
};
class CSFetchSize : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 7862 , TCC0_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(7862);
  // 8054 , TCC1_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(8054);
  // 8246 , TCC2_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(8246);
  // 8438 , TCC3_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(8438);
  // 8630 , TCC4_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(8630);
  // 8822 , TCC5_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(8822);
  // 9014 , TCC6_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9014);
  // 9206 , TCC7_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9206);
  // 9398 , TCC8_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9398);
  // 9590 , TCC9_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9590);
  // 9782 , TCC10_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9782);
  // 9974 , TCC11_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(9974);
  // 10166 , TCC12_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(10166);
  // 10358 , TCC13_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(10358);
  // 10550 , TCC14_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(10550);
  // 10742 , TCC15_TCC_PERF_SEL_MC_RDREQ , gpa_uint64
        // internalCounters.push_back(10742);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSFetchSize", "#ComputeShader#The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
};
class CSWriteSize : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 7853 , TCC0_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(7853);
  // 8045 , TCC1_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(8045);
  // 8237 , TCC2_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(8237);
  // 8429 , TCC3_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(8429);
  // 8621 , TCC4_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(8621);
  // 8813 , TCC5_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(8813);
  // 9005 , TCC6_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9005);
  // 9197 , TCC7_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9197);
  // 9389 , TCC8_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9389);
  // 9581 , TCC9_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9581);
  // 9773 , TCC10_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9773);
  // 9965 , TCC11_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(9965);
  // 10157 , TCC12_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(10157);
  // 10349 , TCC13_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(10349);
  // 10541 , TCC14_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(10541);
  // 10733 , TCC15_TCC_PERF_SEL_MC_WRREQ , gpa_uint64
        // internalCounters.push_back(10733);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSWriteSize", "#ComputeShader#The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
};
class CSCacheHit : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 7845 , TCC0_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(7845);
  // 8037 , TCC1_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8037);
  // 8229 , TCC2_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8229);
  // 8421 , TCC3_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8421);
  // 8613 , TCC4_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8613);
  // 8805 , TCC5_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8805);
  // 8997 , TCC6_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(8997);
  // 9189 , TCC7_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(9189);
  // 9381 , TCC8_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(9381);
  // 9573 , TCC9_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(9573);
  // 9765 , TCC10_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(9765);
  // 9957 , TCC11_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(9957);
  // 10149 , TCC12_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(10149);
  // 10341 , TCC13_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(10341);
  // 10533 , TCC14_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(10533);
  // 10725 , TCC15_TCC_PERF_SEL_HIT , gpa_uint64
        // internalCounters.push_back(10725);
  // 7846 , TCC0_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(7846);
  // 8038 , TCC1_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8038);
  // 8230 , TCC2_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8230);
  // 8422 , TCC3_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8422);
  // 8614 , TCC4_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8614);
  // 8806 , TCC5_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8806);
  // 8998 , TCC6_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(8998);
  // 9190 , TCC7_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(9190);
  // 9382 , TCC8_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(9382);
  // 9574 , TCC9_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(9574);
  // 9766 , TCC10_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(9766);
  // 9958 , TCC11_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(9958);
  // 10150 , TCC12_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(10150);
  // 10342 , TCC13_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(10342);
  // 10534 , TCC14_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(10534);
  // 10726 , TCC15_TCC_PERF_SEL_MISS , gpa_uint64
        // internalCounters.push_back(10726);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSCacheHit", "#ComputeShader#The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*,32,ifnotzero");
};
class CSWriteUnitStalled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 7855 , TCC0_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(7855);
  // 8047 , TCC1_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(8047);
  // 8239 , TCC2_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(8239);
  // 8431 , TCC3_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(8431);
  // 8623 , TCC4_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(8623);
  // 8815 , TCC5_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(8815);
  // 9007 , TCC6_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9007);
  // 9199 , TCC7_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9199);
  // 9391 , TCC8_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9391);
  // 9583 , TCC9_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9583);
  // 9775 , TCC10_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9775);
  // 9967 , TCC11_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(9967);
  // 10159 , TCC12_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(10159);
  // 10351 , TCC13_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(10351);
  // 10543 , TCC14_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(10543);
  // 10735 , TCC15_TCC_PERF_SEL_MC_WRREQ_STALL , gpa_uint64
        // internalCounters.push_back(10735);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);
  // 3289 , SPI_SPI_PERF_CSG_NUM_THREADGROUPS , gpa_uint64
        // internalCounters.push_back(3289);

        // p.DefinePublicCounter("CSWriteUnitStalled", "#ComputeShader#The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,ifnotzero");
};
class CSGDSInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5555 , SQ_CS_SQ_PERF_SEL_INSTS_GDS , gpa_uint64
        // internalCounters.push_back(5555);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSGDSInsts", "#ComputeShader#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
};
class CSLDSInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5554 , SQ_CS_SQ_PERF_SEL_INSTS_LDS , gpa_uint64
        // internalCounters.push_back(5554);
  // 5552 , SQ_CS_SQ_PERF_SEL_INSTS_FLAT , gpa_uint64
        // internalCounters.push_back(5552);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSLDSInsts", "#ComputeShader#The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
};
class CSFlatLDSInsts : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5553 , SQ_CS_SQ_PERF_SEL_INSTS_FLAT_LDS_ONLY , gpa_uint64
        // internalCounters.push_back(5553);
  // 5524 , SQ_CS_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(5524);

        // p.DefinePublicCounter("CSFlatLDSInsts", "#ComputeShader#The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
};
class CSALUStalledByLDS : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 3488 , SQ_SQ_PERF_SEL_WAIT_INST_LDS , gpa_uint64
        // internalCounters.push_back(3488);
  // 3431 , SQ_SQ_PERF_SEL_WAVES , gpa_uint64
        // internalCounters.push_back(3431);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("CSALUStalledByLDS", "#ComputeShader#The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero");
};
class CSLDSBankConflict : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5617 , SQ_CS_SQ_PERF_SEL_LDS_BANK_CONFLICT , gpa_uint64
        // internalCounters.push_back(5617);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("CSLDSBankConflict", "#ComputeShader#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*");
};
class TexUnitBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5868 , TA0_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(5868);
  // 5987 , TA1_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(5987);
  // 6106 , TA2_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6106);
  // 6225 , TA3_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6225);
  // 6344 , TA4_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6344);
  // 6463 , TA5_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6463);
  // 6582 , TA6_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6582);
  // 6701 , TA7_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6701);
  // 6820 , TA8_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6820);
  // 6939 , TA9_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(6939);
  // 7058 , TA10_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7058);
  // 7177 , TA11_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7177);
  // 7296 , TA12_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7296);
  // 7415 , TA13_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7415);
  // 7534 , TA14_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7534);
  // 7653 , TA15_TA_PERF_SEL_TA_BUSY , gpa_uint64
        // internalCounters.push_back(7653);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("TexUnitBusy", "#Timing#The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
};
class TexTriFilteringPct : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5922 , TA0_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(5922);
  // 6041 , TA1_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6041);
  // 6160 , TA2_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6160);
  // 6279 , TA3_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6279);
  // 6398 , TA4_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6398);
  // 6517 , TA5_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6517);
  // 6636 , TA6_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6636);
  // 6755 , TA7_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6755);
  // 6874 , TA8_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6874);
  // 6993 , TA9_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6993);
  // 7112 , TA10_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7112);
  // 7231 , TA11_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7231);
  // 7350 , TA12_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7350);
  // 7469 , TA13_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7469);
  // 7588 , TA14_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7588);
  // 7707 , TA15_TA_PERF_SEL_MIP_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7707);
  // 5921 , TA0_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(5921);
  // 6040 , TA1_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6040);
  // 6159 , TA2_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6159);
  // 6278 , TA3_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6278);
  // 6397 , TA4_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6397);
  // 6516 , TA5_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6516);
  // 6635 , TA6_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6635);
  // 6754 , TA7_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6754);
  // 6873 , TA8_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6873);
  // 6992 , TA9_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6992);
  // 7111 , TA10_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7111);
  // 7230 , TA11_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7230);
  // 7349 , TA12_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7349);
  // 7468 , TA13_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7468);
  // 7587 , TA14_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7587);
  // 7706 , TA15_TA_PERF_SEL_MIP_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7706);

        // p.DefinePublicCounter("TexTriFilteringPct", "#TextureUnit#Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*");
};
class TexVolFilteringPct : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5924 , TA0_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(5924);
  // 6043 , TA1_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6043);
  // 6162 , TA2_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6162);
  // 6281 , TA3_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6281);
  // 6400 , TA4_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6400);
  // 6519 , TA5_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6519);
  // 6638 , TA6_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6638);
  // 6757 , TA7_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6757);
  // 6876 , TA8_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6876);
  // 6995 , TA9_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6995);
  // 7114 , TA10_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7114);
  // 7233 , TA11_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7233);
  // 7352 , TA12_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7352);
  // 7471 , TA13_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7471);
  // 7590 , TA14_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7590);
  // 7709 , TA15_TA_PERF_SEL_VOL_2_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7709);
  // 5923 , TA0_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(5923);
  // 6042 , TA1_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6042);
  // 6161 , TA2_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6161);
  // 6280 , TA3_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6280);
  // 6399 , TA4_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6399);
  // 6518 , TA5_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6518);
  // 6637 , TA6_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6637);
  // 6756 , TA7_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6756);
  // 6875 , TA8_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6875);
  // 6994 , TA9_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(6994);
  // 7113 , TA10_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7113);
  // 7232 , TA11_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7232);
  // 7351 , TA12_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7351);
  // 7470 , TA13_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7470);
  // 7589 , TA14_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7589);
  // 7708 , TA15_TA_PERF_SEL_VOL_1_CYCLE_PIXELS , gpa_uint64
        // internalCounters.push_back(7708);

        // p.DefinePublicCounter("TexVolFilteringPct", "#TextureUnit#Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*");
};
class TexAveAnisotropy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 5942 , TA0_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5942);
  // 6061 , TA1_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6061);
  // 6180 , TA2_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6180);
  // 6299 , TA3_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6299);
  // 6418 , TA4_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6418);
  // 6537 , TA5_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6537);
  // 6656 , TA6_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6656);
  // 6775 , TA7_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6775);
  // 6894 , TA8_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6894);
  // 7013 , TA9_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7013);
  // 7132 , TA10_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7132);
  // 7251 , TA11_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7251);
  // 7370 , TA12_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7370);
  // 7489 , TA13_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7489);
  // 7608 , TA14_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7608);
  // 7727 , TA15_TA_PERF_SEL_ANISO_1_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7727);
  // 5943 , TA0_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5943);
  // 6062 , TA1_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6062);
  // 6181 , TA2_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6181);
  // 6300 , TA3_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6300);
  // 6419 , TA4_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6419);
  // 6538 , TA5_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6538);
  // 6657 , TA6_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6657);
  // 6776 , TA7_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6776);
  // 6895 , TA8_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6895);
  // 7014 , TA9_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7014);
  // 7133 , TA10_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7133);
  // 7252 , TA11_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7252);
  // 7371 , TA12_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7371);
  // 7490 , TA13_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7490);
  // 7609 , TA14_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7609);
  // 7728 , TA15_TA_PERF_SEL_ANISO_2_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7728);
  // 5944 , TA0_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5944);
  // 6063 , TA1_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6063);
  // 6182 , TA2_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6182);
  // 6301 , TA3_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6301);
  // 6420 , TA4_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6420);
  // 6539 , TA5_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6539);
  // 6658 , TA6_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6658);
  // 6777 , TA7_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6777);
  // 6896 , TA8_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6896);
  // 7015 , TA9_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7015);
  // 7134 , TA10_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7134);
  // 7253 , TA11_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7253);
  // 7372 , TA12_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7372);
  // 7491 , TA13_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7491);
  // 7610 , TA14_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7610);
  // 7729 , TA15_TA_PERF_SEL_ANISO_4_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7729);
  // 5945 , TA0_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5945);
  // 6064 , TA1_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6064);
  // 6183 , TA2_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6183);
  // 6302 , TA3_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6302);
  // 6421 , TA4_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6421);
  // 6540 , TA5_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6540);
  // 6659 , TA6_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6659);
  // 6778 , TA7_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6778);
  // 6897 , TA8_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6897);
  // 7016 , TA9_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7016);
  // 7135 , TA10_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7135);
  // 7254 , TA11_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7254);
  // 7373 , TA12_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7373);
  // 7492 , TA13_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7492);
  // 7611 , TA14_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7611);
  // 7730 , TA15_TA_PERF_SEL_ANISO_6_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7730);
  // 5946 , TA0_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5946);
  // 6065 , TA1_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6065);
  // 6184 , TA2_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6184);
  // 6303 , TA3_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6303);
  // 6422 , TA4_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6422);
  // 6541 , TA5_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6541);
  // 6660 , TA6_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6660);
  // 6779 , TA7_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6779);
  // 6898 , TA8_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6898);
  // 7017 , TA9_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7017);
  // 7136 , TA10_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7136);
  // 7255 , TA11_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7255);
  // 7374 , TA12_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7374);
  // 7493 , TA13_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7493);
  // 7612 , TA14_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7612);
  // 7731 , TA15_TA_PERF_SEL_ANISO_8_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7731);
  // 5947 , TA0_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5947);
  // 6066 , TA1_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6066);
  // 6185 , TA2_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6185);
  // 6304 , TA3_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6304);
  // 6423 , TA4_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6423);
  // 6542 , TA5_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6542);
  // 6661 , TA6_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6661);
  // 6780 , TA7_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6780);
  // 6899 , TA8_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6899);
  // 7018 , TA9_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7018);
  // 7137 , TA10_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7137);
  // 7256 , TA11_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7256);
  // 7375 , TA12_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7375);
  // 7494 , TA13_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7494);
  // 7613 , TA14_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7613);
  // 7732 , TA15_TA_PERF_SEL_ANISO_10_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7732);
  // 5948 , TA0_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5948);
  // 6067 , TA1_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6067);
  // 6186 , TA2_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6186);
  // 6305 , TA3_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6305);
  // 6424 , TA4_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6424);
  // 6543 , TA5_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6543);
  // 6662 , TA6_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6662);
  // 6781 , TA7_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6781);
  // 6900 , TA8_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6900);
  // 7019 , TA9_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7019);
  // 7138 , TA10_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7138);
  // 7257 , TA11_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7257);
  // 7376 , TA12_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7376);
  // 7495 , TA13_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7495);
  // 7614 , TA14_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7614);
  // 7733 , TA15_TA_PERF_SEL_ANISO_12_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7733);
  // 5949 , TA0_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5949);
  // 6068 , TA1_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6068);
  // 6187 , TA2_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6187);
  // 6306 , TA3_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6306);
  // 6425 , TA4_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6425);
  // 6544 , TA5_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6544);
  // 6663 , TA6_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6663);
  // 6782 , TA7_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6782);
  // 6901 , TA8_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6901);
  // 7020 , TA9_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7020);
  // 7139 , TA10_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7139);
  // 7258 , TA11_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7258);
  // 7377 , TA12_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7377);
  // 7496 , TA13_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7496);
  // 7615 , TA14_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7615);
  // 7734 , TA15_TA_PERF_SEL_ANISO_14_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7734);
  // 5950 , TA0_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(5950);
  // 6069 , TA1_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6069);
  // 6188 , TA2_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6188);
  // 6307 , TA3_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6307);
  // 6426 , TA4_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6426);
  // 6545 , TA5_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6545);
  // 6664 , TA6_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6664);
  // 6783 , TA7_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6783);
  // 6902 , TA8_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(6902);
  // 7021 , TA9_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7021);
  // 7140 , TA10_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7140);
  // 7259 , TA11_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7259);
  // 7378 , TA12_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7378);
  // 7497 , TA13_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7497);
  // 7616 , TA14_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7616);
  // 7735 , TA15_TA_PERF_SEL_ANISO_16_CYCLE_QUADS , gpa_uint64
        // internalCounters.push_back(7735);

        // p.DefinePublicCounter("TexAveAnisotropy", "#TextureUnit#The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/");
};
class DepthStencilTestBusy : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1747 , DB0_DB_PERF_SEL_OP_PIPE_BUSY , gpa_uint64
        // internalCounters.push_back(1747);
  // 2004 , DB1_DB_PERF_SEL_OP_PIPE_BUSY , gpa_uint64
        // internalCounters.push_back(2004);
  // 2261 , DB2_DB_PERF_SEL_OP_PIPE_BUSY , gpa_uint64
        // internalCounters.push_back(2261);
  // 2518 , DB3_DB_PERF_SEL_OP_PIPE_BUSY , gpa_uint64
        // internalCounters.push_back(2518);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("DepthStencilTestBusy", "#Timing#Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
};
class HiZTilesAccepted : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1618 , DB0_DB_PERF_SEL_DB_SC_TILE_CULLED , gpa_uint64
        // internalCounters.push_back(1618);
  // 1875 , DB1_DB_PERF_SEL_DB_SC_TILE_CULLED , gpa_uint64
        // internalCounters.push_back(1875);
  // 2132 , DB2_DB_PERF_SEL_DB_SC_TILE_CULLED , gpa_uint64
        // internalCounters.push_back(2132);
  // 2389 , DB3_DB_PERF_SEL_DB_SC_TILE_CULLED , gpa_uint64
        // internalCounters.push_back(2389);
  // 1607 , DB0_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(1607);
  // 1864 , DB1_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(1864);
  // 2121 , DB2_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(2121);
  // 2378 , DB3_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(2378);

        // p.DefinePublicCounter("HiZTilesAccepted", "#DepthAndStencil#Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*");
};
class PreZTilesDetailCulled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1607 , DB0_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(1607);
  // 1864 , DB1_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(1864);
  // 2121 , DB2_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(2121);
  // 2378 , DB3_DB_PERF_SEL_SC_DB_TILE_TILES , gpa_uint64
        // internalCounters.push_back(2378);
  // 1631 , DB0_DB_PERF_SEL_SC_DB_QUAD_KILLED_TILES , gpa_uint64
        // internalCounters.push_back(1631);
  // 1888 , DB1_DB_PERF_SEL_SC_DB_QUAD_KILLED_TILES , gpa_uint64
        // internalCounters.push_back(1888);
  // 2145 , DB2_DB_PERF_SEL_SC_DB_QUAD_KILLED_TILES , gpa_uint64
        // internalCounters.push_back(2145);
  // 2402 , DB3_DB_PERF_SEL_SC_DB_QUAD_KILLED_TILES , gpa_uint64
        // internalCounters.push_back(2402);

        // p.DefinePublicCounter("PreZTilesDetailCulled", "#DepthAndStencil#Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*");
};
class HiZQuadsCulled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2996 , PA_SC_SC_QZ0_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2996);
  // 2997 , PA_SC_SC_QZ1_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2997);
  // 2998 , PA_SC_SC_QZ2_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2998);
  // 2999 , PA_SC_SC_QZ3_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2999);
  // 3072 , PA_SC_SC_P0_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3072);
  // 3073 , PA_SC_SC_P1_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3073);
  // 3074 , PA_SC_SC_P2_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3074);
  // 3075 , PA_SC_SC_P3_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3075);

        // p.DefinePublicCounter("HiZQuadsCulled", "#DepthAndStencil#Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*");
};
class PreZQuadsCulled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 2996 , PA_SC_SC_QZ0_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2996);
  // 2997 , PA_SC_SC_QZ1_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2997);
  // 2998 , PA_SC_SC_QZ2_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2998);
  // 2999 , PA_SC_SC_QZ3_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2999);
  // 3096 , PA_SC_SC_EARLYZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3096);
  // 3072 , PA_SC_SC_P0_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3072);
  // 3073 , PA_SC_SC_P1_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3073);
  // 3074 , PA_SC_SC_P2_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3074);
  // 3075 , PA_SC_SC_P3_HIZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3075);

        // p.DefinePublicCounter("PreZQuadsCulled", "#DepthAndStencil#Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*");
};
class PostZQuads : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 3096 , PA_SC_SC_EARLYZ_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(3096);
  // 2996 , PA_SC_SC_QZ0_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2996);
  // 2997 , PA_SC_SC_QZ1_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2997);
  // 2998 , PA_SC_SC_QZ2_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2998);
  // 2999 , PA_SC_SC_QZ3_QUAD_COUNT , gpa_uint64
        // internalCounters.push_back(2999);

        // p.DefinePublicCounter("PostZQuads", "#DepthAndStencil#Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*");
};
class PreZSamplesPassing : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1780 , DB0_DB_PERF_SEL_PREZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(1780);
  // 2037 , DB1_DB_PERF_SEL_PREZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2037);
  // 2294 , DB2_DB_PERF_SEL_PREZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2294);
  // 2551 , DB3_DB_PERF_SEL_PREZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2551);

        // p.DefinePublicCounter("PreZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PreZSamplesFailingS : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1782 , DB0_DB_PERF_SEL_PREZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(1782);
  // 2039 , DB1_DB_PERF_SEL_PREZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2039);
  // 2296 , DB2_DB_PERF_SEL_PREZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2296);
  // 2553 , DB3_DB_PERF_SEL_PREZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2553);

        // p.DefinePublicCounter("PreZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PreZSamplesFailingZ : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1781 , DB0_DB_PERF_SEL_PREZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(1781);
  // 2038 , DB1_DB_PERF_SEL_PREZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2038);
  // 2295 , DB2_DB_PERF_SEL_PREZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2295);
  // 2552 , DB3_DB_PERF_SEL_PREZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2552);

        // p.DefinePublicCounter("PreZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PostZSamplesPassing : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1777 , DB0_DB_PERF_SEL_POSTZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(1777);
  // 2034 , DB1_DB_PERF_SEL_POSTZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2034);
  // 2291 , DB2_DB_PERF_SEL_POSTZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2291);
  // 2548 , DB3_DB_PERF_SEL_POSTZ_SAMPLES_PASSING_Z , gpa_uint64
        // internalCounters.push_back(2548);

        // p.DefinePublicCounter("PostZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PostZSamplesFailingS : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1779 , DB0_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(1779);
  // 2036 , DB1_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2036);
  // 2293 , DB2_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2293);
  // 2550 , DB3_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_S , gpa_uint64
        // internalCounters.push_back(2550);

        // p.DefinePublicCounter("PostZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class PostZSamplesFailingZ : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1778 , DB0_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(1778);
  // 2035 , DB1_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2035);
  // 2292 , DB2_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2292);
  // 2549 , DB3_DB_PERF_SEL_POSTZ_SAMPLES_FAILING_Z , gpa_uint64
        // internalCounters.push_back(2549);

        // p.DefinePublicCounter("PostZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
};
class ZUnitStalled : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 1649 , DB0_DB_PERF_SEL_DB_CB_LQUAD_STALLS , gpa_uint64
        // internalCounters.push_back(1649);
  // 1906 , DB1_DB_PERF_SEL_DB_CB_LQUAD_STALLS , gpa_uint64
        // internalCounters.push_back(1906);
  // 2163 , DB2_DB_PERF_SEL_DB_CB_LQUAD_STALLS , gpa_uint64
        // internalCounters.push_back(2163);
  // 2420 , DB3_DB_PERF_SEL_DB_CB_LQUAD_STALLS , gpa_uint64
        // internalCounters.push_back(2420);
  // 2633 , GRBM_GRBM_PERF_SEL_GUI_ACTIVE , gpa_uint64
        // internalCounters.push_back(2633);

        // p.DefinePublicCounter("ZUnitStalled", "#DepthAndStencil#The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
};
class CBMemRead : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 128 , CB0_CB_PERF_SEL_CC_MC_READ_REQUEST , gpa_uint64
        // internalCounters.push_back(128);
  // 524 , CB1_CB_PERF_SEL_CC_MC_READ_REQUEST , gpa_uint64
        // internalCounters.push_back(524);
  // 920 , CB2_CB_PERF_SEL_CC_MC_READ_REQUEST , gpa_uint64
        // internalCounters.push_back(920);
  // 1316 , CB3_CB_PERF_SEL_CC_MC_READ_REQUEST , gpa_uint64
        // internalCounters.push_back(1316);

        // p.DefinePublicCounter("CBMemRead", "#ColorBuffer#Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
};
class CBMemWritten : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 118 , CB0_CB_PERF_SEL_CC_MC_WRITE_REQUEST , gpa_uint64
        // internalCounters.push_back(118);
  // 514 , CB1_CB_PERF_SEL_CC_MC_WRITE_REQUEST , gpa_uint64
        // internalCounters.push_back(514);
  // 910 , CB2_CB_PERF_SEL_CC_MC_WRITE_REQUEST , gpa_uint64
        // internalCounters.push_back(910);
  // 1306 , CB3_CB_PERF_SEL_CC_MC_WRITE_REQUEST , gpa_uint64
        // internalCounters.push_back(1306);

        // p.DefinePublicCounter("CBMemWritten", "#ColorBuffer#Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
};
class CBSlowPixelPct : public AMDMetric {
        // vector< gpa_uint32 > internalCounters;
  // 162 , CB0_CB_PERF_SEL_EXPORT_32_ABGR_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(162);
  // 558 , CB1_CB_PERF_SEL_EXPORT_32_ABGR_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(558);
  // 954 , CB2_CB_PERF_SEL_EXPORT_32_ABGR_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(954);
  // 1350 , CB3_CB_PERF_SEL_EXPORT_32_ABGR_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(1350);
  // 7 , CB0_CB_PERF_SEL_DRAWN_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(7);
  // 403 , CB1_CB_PERF_SEL_DRAWN_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(403);
  // 799 , CB2_CB_PERF_SEL_DRAWN_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(799);
  // 1195 , CB3_CB_PERF_SEL_DRAWN_QUAD_FRAGMENT , gpa_uint64
        // internalCounters.push_back(1195);

        // p.DefinePublicCounter("CBSlowPixelPct", "#ColorBuffer#Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min");
};
