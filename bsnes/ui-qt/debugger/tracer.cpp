#include "tracer.moc"
Tracer *tracer;

void Tracer::stepCpu() {
  if(traceCpu) {
    unsigned addr = SNES::cpu.regs.pc;
    if(!traceMask || !(traceMaskCPU[addr >> 3] & (0x80 >> (addr & 7)))) {
      char text[256];
      SNES::cpu.disassemble_opcode(text, addr);
      tracefile.print(string() << text << "\n");
    }
    traceMaskCPU[addr >> 3] |= 0x80 >> (addr & 7);
  }
}

void Tracer::stepSmp() {
  if(traceSmp) {
    unsigned addr = SNES::smp.regs.pc;
    if(!traceMask || !(traceMaskSMP[addr >> 3] & (0x80 >> (addr & 7)))) {
      char text[256];
      SNES::smp.disassemble_opcode(text, addr);
      tracefile.print(string() << text << "\n");
    }
    traceMaskSMP[addr >> 3] |= 0x80 >> (addr & 7);
  }
}

void Tracer::stepSa1() {
  if(traceSa1) {
    unsigned addr = SNES::sa1.regs.pc;
    if(!traceMask || !(traceMaskSA1[addr >> 3] & (0x80 >> (addr & 7)))) {
      char text[256];
      SNES::sa1.disassemble_opcode(text, addr);
      tracefile.print(string() << text << "\n");
    }
    traceMaskSA1[addr >> 3] |= 0x80 >> (addr & 7);
  }
}

void Tracer::stepSfx() {
  if(traceSfx) {
    unsigned addr = SNES::superfx.regs.r[15] + (SNES::superfx.regs.pbr << 16);
    if(!traceMask || !(traceMaskSFX[addr >> 3] & (0x80 >> (addr & 7)))) {
      char text[256];
      SNES::superfx.disassemble_opcode(text, addr);
      tracefile.print(string() << text << "\n");
    }
    traceMaskSA1[addr >> 3] |= 0x80 >> (addr & 7);
  }
}

void Tracer::setCpuTraceState(int state) {
  traceCpu = (state == Qt::Checked);

  if(traceCpu && !tracefile.open()) {
    tracefile.open(string() << config().path.data << "trace.log", file::mode::write);
  } else if(!traceCpu && !traceSmp && !traceSa1 && !traceSfx && tracefile.open()) {
    tracefile.close();
  }
}

void Tracer::setSmpTraceState(int state) {
  traceSmp = (state == Qt::Checked);

  if(traceSmp && !tracefile.open()) {
    tracefile.open(string() << config().path.data << "trace.log", file::mode::write);
  } else if(!traceCpu && !traceSmp && !traceSa1 && !traceSfx && tracefile.open()) {
    tracefile.close();
  }
}

void Tracer::setSa1TraceState(int state) {
  traceSa1 = (state == Qt::Checked);

  if(traceSa1 && !tracefile.open()) {
    tracefile.open(string() << config().path.data << "trace.log", file::mode::write);
  } else if(!traceCpu && !traceSmp && !traceSa1 && !traceSfx && tracefile.open()) {
    tracefile.close();
  }
}

void Tracer::setSfxTraceState(int state) {
  traceSfx = (state == Qt::Checked);

  if(traceSfx && !tracefile.open()) {
    tracefile.open(string() << config().path.data << "trace.log", file::mode::write);
  } else if(!traceCpu && !traceSmp && !traceSa1 && !traceSfx && tracefile.open()) {
    tracefile.close();
  }
}

void Tracer::setTraceMaskState(int state) {
  traceMask = (state == Qt::Checked);

  if(traceMask) {
    //flush all bitmasks once enabled
    memset(traceMaskCPU, 0x00, (1 << 24) >> 3);
    memset(traceMaskSMP, 0x00, (1 << 16) >> 3);
    memset(traceMaskSA1, 0x00, (1 << 16) >> 3);
    memset(traceMaskSFX, 0x00, (1 << 16) >> 3);
  }
}

Tracer::Tracer() {
  traceCpu = false;
  traceSmp = false;
  traceSa1 = false;
  traceSfx = false;
  traceMask = false;

  traceMaskCPU = new uint8_t[(1 << 24) >> 3]();
  traceMaskSMP = new uint8_t[(1 << 16) >> 3]();
  traceMaskSA1 = new uint8_t[(1 << 16) >> 3]();
  traceMaskSFX = new uint8_t[(1 << 16) >> 3]();

  SNES::cpu.step_event = { &Tracer::stepCpu, this };
  SNES::smp.step_event = { &Tracer::stepSmp, this };
  SNES::sa1.step_event = { &Tracer::stepSa1, this };
  SNES::superfx.step_event = { &Tracer::stepSfx, this };
}

Tracer::~Tracer() {
  delete[] traceMaskCPU;
  delete[] traceMaskSMP;
  delete[] traceMaskSA1;
  delete[] traceMaskSFX;
  if(tracefile.open()) tracefile.close();
}
