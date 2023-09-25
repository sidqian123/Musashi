<details> <summary>unsigned int m68k_read_memory_8(unsigned int address)
</summary>     m68ki_exception_address_error (m68kcpu.h)

<details> <summary>    m68ki_exception_bus_error (m68kcpu.h)
</summary>         m68k_pulse_bus_error (m68kcpu.c)

</details><details> <summary>    m68ki_read_8_fc (m68kcpu.h)
</summary>         OPER_A7_PD_8 (m68kcpu.h)

        OPER_A7_PI_8 (m68kcpu.h)

        OPER_AL_8 (m68kcpu.h)

        OPER_AW_8 (m68kcpu.h)

        OPER_AX_AI_8 (m68kcpu.h)

        OPER_AX_DI_8 (m68kcpu.h)

        OPER_AX_IX_8 (m68kcpu.h)

        OPER_AX_PD_8 (m68kcpu.h)

        OPER_AX_PI_8 (m68kcpu.h)

        OPER_AY_AI_8 (m68kcpu.h)

        OPER_AY_DI_8 (m68kcpu.h)

        OPER_AY_IX_8 (m68kcpu.h)

        OPER_AY_PD_8 (m68kcpu.h)

        OPER_AY_PI_8 (m68kcpu.h)

<details> <summary>        READ_EA_8 (m68kfpu.c)(5 usages)
</summary> <details> <summary>            fpgen_rm_reg (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details></details></details></details><details> <summary>unsigned int m68k_read_memory_16(unsigned int address)
</summary> <details> <summary>    m68ki_read_16_fc (m68kcpu.h)
</summary> <details> <summary>        load_extended_float80 (m68kfpu.c)
</summary> <details> <summary>            READ_EA_FPE (m68kfpu.c)(6 usages)
</summary> <details> <summary>                fmovem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details>        m68ki_pull_16 (m68kcpu.h)

        OPER_AL_16 (m68kcpu.h)

        OPER_AW_16 (m68kcpu.h)

        OPER_AX_AI_16 (m68kcpu.h)

        OPER_AX_DI_16 (m68kcpu.h)

        OPER_AX_IX_16 (m68kcpu.h)

        OPER_AX_PD_16 (m68kcpu.h)

        OPER_AX_PI_16 (m68kcpu.h)

        OPER_AY_AI_16 (m68kcpu.h)

        OPER_AY_DI_16 (m68kcpu.h)

        OPER_AY_IX_16 (m68kcpu.h)

        OPER_AY_PD_16 (m68kcpu.h)

        OPER_AY_PI_16 (m68kcpu.h)

<details> <summary>        READ_EA_16 (m68kfpu.c)(5 usages)
</summary> <details> <summary>            fpgen_rm_reg (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details></details></details></details><details> <summary>unsigned int m68k_read_memory_32(unsigned int address)
</summary> <details> <summary>    m68ki_read_32_fc (m68kcpu.h)
</summary> <details> <summary>        load_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>            READ_EA_FPE (m68kfpu.c)(6 usages)
</summary> <details> <summary>                fmovem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        load_pack_float80 (m68kfpu.c)(3 usages)
</summary> <details> <summary>            READ_EA_PACK (m68kfpu.c)(3 usages)
</summary> <details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_exception_interrupt (m68kcpu.h)(2 usages)
</summary> <details> <summary>            m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                m68k_execute (m68kcpu.c)
</summary> <details> <summary>                    emulator_tick (sim.c)
</summary>                         main (sim.c)

</details></details>                m68ki_set_sr (m68kcpu.h)

</details></details><details> <summary>        m68ki_get_ea_ix (m68kcpu.h)(2 usages)
</summary> <details> <summary>            m68ki_get_ea_pcix (m68kcpu.h)
</summary>                 OPER_PCIX_8 (m68kcpu.h)

</details>            OPER_AX_IX_8 (m68kcpu.h)

            OPER_AY_IX_8 (m68kcpu.h)

<details> <summary>            READ_EA_8 (m68kfpu.c)
</summary> <details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details><details> <summary>            WRITE_EA_8 (m68kfpu.c)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_jump_vector (m68kcpu.h)
</summary>             m68ki_exception_1010 (m68kcpu.h)

            m68ki_exception_1111 (m68kcpu.h)

            m68ki_exception_address_error (m68kcpu.h)

<details> <summary>            m68ki_exception_bus_error (m68kcpu.h)
</summary>                 m68k_pulse_bus_error (m68kcpu.c)

</details>            m68ki_exception_format_error (m68kcpu.h)

            m68ki_exception_illegal (m68kcpu.h)

            m68ki_exception_privilege_violation (m68kcpu.h)

            m68ki_exception_trace (m68kcpu.h)

            m68ki_exception_trap (m68kcpu.h)

            m68ki_exception_trapN (m68kcpu.h)

</details>        m68ki_pull_32 (m68kcpu.h)

        m68040_fpu_op1 (m68kfpu.c)(2 usages)

        OPER_AL_32 (m68kcpu.h)

        OPER_AW_32 (m68kcpu.h)

        OPER_AX_AI_32 (m68kcpu.h)

        OPER_AX_DI_32 (m68kcpu.h)

        OPER_AX_IX_32 (m68kcpu.h)

        OPER_AX_PD_32 (m68kcpu.h)

        OPER_AX_PI_32 (m68kcpu.h)

        OPER_AY_AI_32 (m68kcpu.h)

        OPER_AY_DI_32 (m68kcpu.h)

        OPER_AY_IX_32 (m68kcpu.h)

        OPER_AY_PD_32 (m68kcpu.h)

        OPER_AY_PI_32 (m68kcpu.h)

<details> <summary>        READ_EA_32 (m68kfpu.c)(7 usages)
</summary> <details> <summary>            fmove_fpcr (m68kfpu.c)(3 usages)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>            fpgen_rm_reg (m68kfpu.c)(2 usages)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details>            m68881_mmu_ops (m68kmmu.h)(2 usages)

</details><details> <summary>        READ_EA_64 (m68kfpu.c)(8 usages)
</summary> <details> <summary>            fpgen_rm_reg (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details>            m68881_mmu_ops (m68kmmu.h)(2 usages)

</details></details><details> <summary>    pmmu_translate_addr (m68kmmu.h)(9 usages)
</summary> <details> <summary>        m68ki_read_8_fc (m68kcpu.h)
</summary>             OPER_A7_PD_8 (m68kcpu.h)

            OPER_A7_PI_8 (m68kcpu.h)

            OPER_AL_8 (m68kcpu.h)

            OPER_AW_8 (m68kcpu.h)

            OPER_AX_AI_8 (m68kcpu.h)

            OPER_AX_DI_8 (m68kcpu.h)

            OPER_AX_IX_8 (m68kcpu.h)

            OPER_AX_PD_8 (m68kcpu.h)

            OPER_AX_PI_8 (m68kcpu.h)

            OPER_AY_AI_8 (m68kcpu.h)

            OPER_AY_DI_8 (m68kcpu.h)

            OPER_AY_IX_8 (m68kcpu.h)

            OPER_AY_PD_8 (m68kcpu.h)

            OPER_AY_PI_8 (m68kcpu.h)

<details> <summary>            READ_EA_8 (m68kfpu.c)(5 usages)
</summary> <details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_read_16_fc (m68kcpu.h)
</summary> <details> <summary>            load_extended_float80 (m68kfpu.c)
</summary> <details> <summary>                READ_EA_FPE (m68kfpu.c)(6 usages)
</summary> <details> <summary>                    fmovem (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                    fpgen_rm_reg (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details>            m68ki_pull_16 (m68kcpu.h)

            OPER_AL_16 (m68kcpu.h)

            OPER_AW_16 (m68kcpu.h)

            OPER_AX_AI_16 (m68kcpu.h)

            OPER_AX_DI_16 (m68kcpu.h)

            OPER_AX_IX_16 (m68kcpu.h)

            OPER_AX_PD_16 (m68kcpu.h)

            OPER_AX_PI_16 (m68kcpu.h)

            OPER_AY_AI_16 (m68kcpu.h)

            OPER_AY_DI_16 (m68kcpu.h)

            OPER_AY_IX_16 (m68kcpu.h)

            OPER_AY_PD_16 (m68kcpu.h)

            OPER_AY_PI_16 (m68kcpu.h)

<details> <summary>            READ_EA_16 (m68kfpu.c)(5 usages)
</summary> <details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_read_32_fc (m68kcpu.h)
</summary> <details> <summary>            load_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>                READ_EA_FPE (m68kfpu.c)(6 usages)
</summary> <details> <summary>                    fmovem (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                    fpgen_rm_reg (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            load_pack_float80 (m68kfpu.c)(3 usages)
</summary> <details> <summary>                READ_EA_PACK (m68kfpu.c)(3 usages)
</summary> <details> <summary>                    fpgen_rm_reg (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            m68ki_exception_interrupt (m68kcpu.h)(2 usages)
</summary> <details> <summary>                m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                    m68k_execute (m68kcpu.c)
</summary> <details> <summary>                        emulator_tick (sim.c)
</summary>                             main (sim.c)

</details></details>                    m68ki_set_sr (m68kcpu.h)

</details></details><details> <summary>            m68ki_get_ea_ix (m68kcpu.h)(2 usages)
</summary> <details> <summary>                m68ki_get_ea_pcix (m68kcpu.h)
</summary>                     OPER_PCIX_8 (m68kcpu.h)

</details>                OPER_AX_IX_8 (m68kcpu.h)

                OPER_AY_IX_8 (m68kcpu.h)

<details> <summary>                READ_EA_8 (m68kfpu.c)
</summary> <details> <summary>                    fpgen_rm_reg (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details><details> <summary>                WRITE_EA_8 (m68kfpu.c)
</summary> <details> <summary>                    fmove_reg_mem (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            m68ki_jump_vector (m68kcpu.h)
</summary>                 m68ki_exception_1010 (m68kcpu.h)

                m68ki_exception_1111 (m68kcpu.h)

                m68ki_exception_address_error (m68kcpu.h)

<details> <summary>                m68ki_exception_bus_error (m68kcpu.h)
</summary>                     m68k_pulse_bus_error (m68kcpu.c)

</details>                m68ki_exception_format_error (m68kcpu.h)

                m68ki_exception_illegal (m68kcpu.h)

                m68ki_exception_privilege_violation (m68kcpu.h)

                m68ki_exception_trace (m68kcpu.h)

                m68ki_exception_trap (m68kcpu.h)

                m68ki_exception_trapN (m68kcpu.h)

</details>            m68ki_pull_32 (m68kcpu.h)

            m68040_fpu_op1 (m68kfpu.c)(2 usages)

            OPER_AL_32 (m68kcpu.h)

            OPER_AW_32 (m68kcpu.h)

            OPER_AX_AI_32 (m68kcpu.h)

            OPER_AX_DI_32 (m68kcpu.h)

            OPER_AX_IX_32 (m68kcpu.h)

            OPER_AX_PD_32 (m68kcpu.h)

            OPER_AX_PI_32 (m68kcpu.h)

            OPER_AY_AI_32 (m68kcpu.h)

            OPER_AY_DI_32 (m68kcpu.h)

            OPER_AY_IX_32 (m68kcpu.h)

            OPER_AY_PD_32 (m68kcpu.h)

            OPER_AY_PI_32 (m68kcpu.h)

<details> <summary>            READ_EA_32 (m68kfpu.c)(7 usages)
</summary> <details> <summary>                fmove_fpcr (m68kfpu.c)(3 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fpgen_rm_reg (m68kfpu.c)(2 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details>                m68881_mmu_ops (m68kmmu.h)(2 usages)

</details><details> <summary>            READ_EA_64 (m68kfpu.c)(8 usages)
</summary> <details> <summary>                fpgen_rm_reg (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details>                m68881_mmu_ops (m68kmmu.h)(2 usages)

</details></details><details> <summary>        m68ki_write_8_fc (m68kcpu.h)
</summary> <details> <summary>            fscc (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>            WRITE_EA_8 (m68kfpu.c)(7 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_write_16_fc (m68kcpu.h)
</summary> <details> <summary>            m68ki_push_16 (m68kcpu.h)
</summary> <details> <summary>                m68ki_stack_frame_0000 (m68kcpu.h)(2 usages)
</summary>                     m68ki_exception_1010 (m68kcpu.h)

                    m68ki_exception_1111 (m68kcpu.h)

                    m68ki_exception_format_error (m68kcpu.h)

                    m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details>                    m68ki_exception_privilege_violation (m68kcpu.h)

                    m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

                    m68ki_exception_trapN (m68kcpu.h)

</details><details> <summary>                m68ki_stack_frame_0001 (m68kcpu.h)(2 usages)
</summary> <details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details></details><details> <summary>                m68ki_stack_frame_3word (m68kcpu.h)
</summary> <details> <summary>                    m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                         m68ki_exception_1010 (m68kcpu.h)

                        m68ki_exception_1111 (m68kcpu.h)

                        m68ki_exception_format_error (m68kcpu.h)

                        m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                        m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                            m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                                m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                    emulator_tick (sim.c)
</summary>                                         main (sim.c)

</details></details>                                m68ki_set_sr (m68kcpu.h)

</details></details>                        m68ki_exception_privilege_violation (m68kcpu.h)

                        m68ki_exception_trace (m68kcpu.h)

                        m68ki_exception_trap (m68kcpu.h)

                        m68ki_exception_trapN (m68kcpu.h)

</details></details><details> <summary>                m68ki_stack_frame_0010 (m68kcpu.h)(2 usages)
</summary>                     m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

</details><details> <summary>                m68ki_stack_frame_1000 (m68kcpu.h)(6 usages)
</summary> <details> <summary>                    m68ki_exception_bus_error (m68kcpu.h)
</summary>                         m68k_pulse_bus_error (m68kcpu.c)

</details></details>                m68ki_stack_frame_1010 (m68kcpu.h)(10 usages)

                m68ki_stack_frame_1011 (m68kcpu.h)(10 usages)

<details> <summary>                m68ki_stack_frame_buserr (m68kcpu.h)(3 usages)
</summary>                     m68ki_exception_address_error (m68kcpu.h)

</details></details><details> <summary>            store_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>                WRITE_EA_FPE (m68kfpu.c)(4 usages)
</summary> <details> <summary>                    fmove_reg_mem (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                    fmovem (m68kfpu.c)(2 usages)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            WRITE_EA_16 (m68kfpu.c)(7 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        m68ki_write_32_fc (m68kcpu.h)
</summary> <details> <summary>            m68ki_push_32 (m68kcpu.h)
</summary> <details> <summary>                m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                     m68ki_exception_1010 (m68kcpu.h)

                    m68ki_exception_1111 (m68kcpu.h)

                    m68ki_exception_format_error (m68kcpu.h)

                    m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details>                    m68ki_exception_privilege_violation (m68kcpu.h)

                    m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

                    m68ki_exception_trapN (m68kcpu.h)

</details><details> <summary>                m68ki_stack_frame_0001 (m68kcpu.h)
</summary> <details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details></details><details> <summary>                m68ki_stack_frame_3word (m68kcpu.h)
</summary> <details> <summary>                    m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                         m68ki_exception_1010 (m68kcpu.h)

                        m68ki_exception_1111 (m68kcpu.h)

                        m68ki_exception_format_error (m68kcpu.h)

                        m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                        m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                            m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                                m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                    emulator_tick (sim.c)
</summary>                                         main (sim.c)

</details></details>                                m68ki_set_sr (m68kcpu.h)

</details></details>                        m68ki_exception_privilege_violation (m68kcpu.h)

                        m68ki_exception_trace (m68kcpu.h)

                        m68ki_exception_trap (m68kcpu.h)

                        m68ki_exception_trapN (m68kcpu.h)

</details></details><details> <summary>                m68ki_stack_frame_0010 (m68kcpu.h)(2 usages)
</summary>                     m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

</details><details> <summary>                m68ki_stack_frame_1000 (m68kcpu.h)(2 usages)
</summary> <details> <summary>                    m68ki_exception_bus_error (m68kcpu.h)
</summary>                         m68k_pulse_bus_error (m68kcpu.c)

</details></details>                m68ki_stack_frame_1010 (m68kcpu.h)(3 usages)

                m68ki_stack_frame_1011 (m68kcpu.h)(18 usages)

<details> <summary>                m68ki_stack_frame_buserr (m68kcpu.h)(2 usages)
</summary>                     m68ki_exception_address_error (m68kcpu.h)

</details></details>            m68040_fpu_op1 (m68kfpu.c)(2 usages)

<details> <summary>            perform_fsave (m68kfpu.c)(14 usages)
</summary>                 m68040_fpu_op1 (m68kfpu.c)(2 usages)

</details><details> <summary>            store_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>                WRITE_EA_FPE (m68kfpu.c)(4 usages)
</summary> <details> <summary>                    fmove_reg_mem (m68kfpu.c)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                    fmovem (m68kfpu.c)(2 usages)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            store_pack_float80 (m68kfpu.c)(3 usages)
</summary> <details> <summary>                WRITE_EA_PACK (m68kfpu.c)(3 usages)
</summary> <details> <summary>                    fmove_reg_mem (m68kfpu.c)(2 usages)
</summary>                         m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>            WRITE_EA_32 (m68kfpu.c)(7 usages)
</summary> <details> <summary>                fmove_fpcr (m68kfpu.c)(3 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fmove_reg_mem (m68kfpu.c)(2 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details>                m68881_mmu_ops (m68kmmu.h)(2 usages)

</details><details> <summary>            WRITE_EA_64 (m68kfpu.c)(6 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details>                m68881_mmu_ops (m68kmmu.h)(2 usages)

</details></details></details></details><details> <summary>unsigned int m68k_write_memory_8(unsigned int address)
</summary> <details> <summary>    m68ki_write_8_fc (m68kcpu.h)
</summary> <details> <summary>        fscc (m68kfpu.c)
</summary>             m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>        WRITE_EA_8 (m68kfpu.c)(7 usages)
</summary> <details> <summary>            fmove_reg_mem (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details></details></details></details><details> <summary>unsigned int m68k_write_memory_16(unsigned int address)
</summary> <details> <summary>    m68ki_write_16_fc (m68kcpu.h)
</summary> <details> <summary>        m68ki_push_16 (m68kcpu.h)
</summary> <details> <summary>            m68ki_stack_frame_0000 (m68kcpu.h)(2 usages)
</summary>                 m68ki_exception_1010 (m68kcpu.h)

                m68ki_exception_1111 (m68kcpu.h)

                m68ki_exception_format_error (m68kcpu.h)

                m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                    m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                        m68k_execute (m68kcpu.c)
</summary> <details> <summary>                            emulator_tick (sim.c)
</summary>                                 main (sim.c)

</details></details>                        m68ki_set_sr (m68kcpu.h)

</details></details>                m68ki_exception_privilege_violation (m68kcpu.h)

                m68ki_exception_trace (m68kcpu.h)

                m68ki_exception_trap (m68kcpu.h)

                m68ki_exception_trapN (m68kcpu.h)

</details><details> <summary>            m68ki_stack_frame_0001 (m68kcpu.h)(2 usages)
</summary> <details> <summary>                m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                    m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                        m68k_execute (m68kcpu.c)
</summary> <details> <summary>                            emulator_tick (sim.c)
</summary>                                 main (sim.c)

</details></details>                        m68ki_set_sr (m68kcpu.h)

</details></details></details><details> <summary>            m68ki_stack_frame_3word (m68kcpu.h)
</summary> <details> <summary>                m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                     m68ki_exception_1010 (m68kcpu.h)

                    m68ki_exception_1111 (m68kcpu.h)

                    m68ki_exception_format_error (m68kcpu.h)

                    m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details>                    m68ki_exception_privilege_violation (m68kcpu.h)

                    m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

                    m68ki_exception_trapN (m68kcpu.h)

</details></details><details> <summary>            m68ki_stack_frame_0010 (m68kcpu.h)(2 usages)
</summary>                 m68ki_exception_trace (m68kcpu.h)

                m68ki_exception_trap (m68kcpu.h)

</details><details> <summary>            m68ki_stack_frame_1000 (m68kcpu.h)(6 usages)
</summary> <details> <summary>                m68ki_exception_bus_error (m68kcpu.h)
</summary>                     m68k_pulse_bus_error (m68kcpu.c)

</details></details>            m68ki_stack_frame_1010 (m68kcpu.h)(10 usages)

            m68ki_stack_frame_1011 (m68kcpu.h)(10 usages)

<details> <summary>            m68ki_stack_frame_buserr (m68kcpu.h)(3 usages)
</summary>                 m68ki_exception_address_error (m68kcpu.h)

</details></details><details> <summary>        store_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>            WRITE_EA_FPE (m68kfpu.c)(4 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fmovem (m68kfpu.c)(2 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        WRITE_EA_16 (m68kfpu.c)(7 usages)
</summary> <details> <summary>            fmove_reg_mem (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details></details></details></details><details> <summary>unsigned int m68k_write_memory_16(unsigned int address)
</summary> <details> <summary>    m68ki_write_32_fc (m68kcpu.h)
</summary> <details> <summary>        m68ki_push_32 (m68kcpu.h)
</summary> <details> <summary>            m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                 m68ki_exception_1010 (m68kcpu.h)

                m68ki_exception_1111 (m68kcpu.h)

                m68ki_exception_format_error (m68kcpu.h)

                m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                    m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                        m68k_execute (m68kcpu.c)
</summary> <details> <summary>                            emulator_tick (sim.c)
</summary>                                 main (sim.c)

</details></details>                        m68ki_set_sr (m68kcpu.h)

</details></details>                m68ki_exception_privilege_violation (m68kcpu.h)

                m68ki_exception_trace (m68kcpu.h)

                m68ki_exception_trap (m68kcpu.h)

                m68ki_exception_trapN (m68kcpu.h)

</details><details> <summary>            m68ki_stack_frame_0001 (m68kcpu.h)
</summary> <details> <summary>                m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                    m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                        m68k_execute (m68kcpu.c)
</summary> <details> <summary>                            emulator_tick (sim.c)
</summary>                                 main (sim.c)

</details></details>                        m68ki_set_sr (m68kcpu.h)

</details></details></details><details> <summary>            m68ki_stack_frame_3word (m68kcpu.h)
</summary> <details> <summary>                m68ki_stack_frame_0000 (m68kcpu.h)
</summary>                     m68ki_exception_1010 (m68kcpu.h)

                    m68ki_exception_1111 (m68kcpu.h)

                    m68ki_exception_format_error (m68kcpu.h)

                    m68ki_exception_illegal (m68kcpu.h)

<details> <summary>                    m68ki_exception_interrupt (m68kcpu.h)
</summary> <details> <summary>                        m68ki_check_interrupts (m68kcpu.h)(2 usages)
</summary> <details> <summary>                            m68k_execute (m68kcpu.c)
</summary> <details> <summary>                                emulator_tick (sim.c)
</summary>                                     main (sim.c)

</details></details>                            m68ki_set_sr (m68kcpu.h)

</details></details>                    m68ki_exception_privilege_violation (m68kcpu.h)

                    m68ki_exception_trace (m68kcpu.h)

                    m68ki_exception_trap (m68kcpu.h)

                    m68ki_exception_trapN (m68kcpu.h)

</details></details><details> <summary>            m68ki_stack_frame_0010 (m68kcpu.h)(2 usages)
</summary>                 m68ki_exception_trace (m68kcpu.h)

                m68ki_exception_trap (m68kcpu.h)

</details><details> <summary>            m68ki_stack_frame_1000 (m68kcpu.h)(2 usages)
</summary> <details> <summary>                m68ki_exception_bus_error (m68kcpu.h)
</summary>                     m68k_pulse_bus_error (m68kcpu.c)

</details></details>            m68ki_stack_frame_1010 (m68kcpu.h)(3 usages)

            m68ki_stack_frame_1011 (m68kcpu.h)(18 usages)

<details> <summary>            m68ki_stack_frame_buserr (m68kcpu.h)(2 usages)
</summary>                 m68ki_exception_address_error (m68kcpu.h)

</details></details>        m68040_fpu_op1 (m68kfpu.c)(2 usages)

<details> <summary>        perform_fsave (m68kfpu.c)(14 usages)
</summary>             m68040_fpu_op1 (m68kfpu.c)(2 usages)

</details><details> <summary>        store_extended_float80 (m68kfpu.c)(2 usages)
</summary> <details> <summary>            WRITE_EA_FPE (m68kfpu.c)(4 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>                fmovem (m68kfpu.c)(2 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        store_pack_float80 (m68kfpu.c)(3 usages)
</summary> <details> <summary>            WRITE_EA_PACK (m68kfpu.c)(3 usages)
</summary> <details> <summary>                fmove_reg_mem (m68kfpu.c)(2 usages)
</summary>                     m68040_fpu_op0 (m68kfpu.c)

</details></details></details><details> <summary>        WRITE_EA_32 (m68kfpu.c)(7 usages)
</summary> <details> <summary>            fmove_fpcr (m68kfpu.c)(3 usages)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details><details> <summary>            fmove_reg_mem (m68kfpu.c)(2 usages)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details>            m68881_mmu_ops (m68kmmu.h)(2 usages)

</details><details> <summary>        WRITE_EA_64 (m68kfpu.c)(6 usages)
</summary> <details> <summary>            fmove_reg_mem (m68kfpu.c)
</summary>                 m68040_fpu_op0 (m68kfpu.c)

</details></details></details></details>