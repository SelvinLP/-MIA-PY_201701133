import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ConfiguracionUsuComponent } from './configuracion-usu.component';

describe('ConfiguracionUsuComponent', () => {
  let component: ConfiguracionUsuComponent;
  let fixture: ComponentFixture<ConfiguracionUsuComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ConfiguracionUsuComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ConfiguracionUsuComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
